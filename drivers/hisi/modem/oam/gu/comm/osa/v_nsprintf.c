/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "v_IO.h"

#define    THIS_FILE_ID        PS_FILE_ID_V_NSPRINTF_C

VOS_INT32 ANSI_nvsprintf(VOS_CHAR *out_buf, VOS_UINT32 ulStrLen, const VOS_CHAR *fmt0, va_list argp)
{
    VOS_UINT_PTR    ulLong;
    VOS_INT         lBase;
    VOS_INT         lDprec;
    VOS_INT         lFieldSize;
    VOS_INT         lFlags;
    VOS_INT         lFpprec;
    VOS_INT         lPrec;
    VOS_INT         lRealSize;
    VOS_INT         lConverSize;
    VOS_INT         lFormatWidth;
    VOS_INT         lChar;
    VOS_INT         ltemp;

    VOS_UCHAR       *pucFmt;
    VOS_CHAR        *pcBuf;
    VOS_CHAR        ucPrefixSign;
    VOS_CHAR        *pucDigs;
    VOS_CHAR        ucBuf[BUF];
    VOS_CHAR        *pucOutBuf=out_buf;
    VOS_UINT32      ulWriteLen = ulStrLen;

    pucFmt  = (VOS_UCHAR*)fmt0;
    pucDigs = "0123456789abcdef";

    for (;; ++pucFmt)
    {
            for (; ((lChar = *pucFmt)!=0) && lChar != '%'; ++pucFmt)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++ = (VOS_CHAR)lChar;
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }
            if (!lChar)
            {
                goto    lvspret;
            }

            lFlags          = 0;
            lDprec          = 0;
            lFpprec         = 0;
            lFormatWidth    = 0;
            lPrec           = -1;
            ucPrefixSign = '\0';

rflag: switch (*++pucFmt) {
        case ' ':
            if (!ucPrefixSign)
            {
                ucPrefixSign = ' ';
            }
            goto rflag;
        case '#':
            lFlags |= ALT;
            goto rflag;
        case '*':
            if ((lFormatWidth = va_arg(argp, VOS_INT)) >= 0)
            {
                goto rflag;
            }
            lFormatWidth = -lFormatWidth;
        case '-':
            lFlags |= LADJUST;
            goto rflag;
        case '+':
            ucPrefixSign = '+';
            goto rflag;
        case '.':
            if (*++pucFmt == '*')
            {
                ltemp = va_arg(argp, VOS_INT);
            }
            else
            {
                ltemp = 0;
                while (isascii(*pucFmt) && isdigit(*pucFmt))
                {
                    ltemp = 10 * ltemp + todigit(*pucFmt++);
                }
                --pucFmt;
            }
            lPrec = ltemp < 0 ? -1 : ltemp;
            goto rflag;
        case '0':
            lFlags |= ZEROPAD;
            goto rflag;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            ltemp = 0;
            do
            {
                ltemp = 10 * ltemp + todigit(*pucFmt);
            } while (isascii(*++pucFmt) && isdigit(*pucFmt));
            lFormatWidth = ltemp;
            --pucFmt;
            goto rflag;
        case 'L':
            lFlags |= LONGDBL;        
            goto rflag;
        case 'h':
            lFlags |= SHORTINT;          
            goto rflag;    
        case 'l':
            lFlags |= LONGINT;      
            goto rflag;     
        case 'c':
            *(pcBuf = ucBuf) = (VOS_CHAR)va_arg(argp, VOS_INT);
            lConverSize = 1;
            ucPrefixSign = '\0';       
            goto pforw;
        case 'D':
            lFlags |= LONGINT;
        case 'd':
        case 'i':
            ARG(int);
            if ((VOS_INT32)ulLong < 0)
            {
                ulLong = -ulLong;
                ucPrefixSign = '-';
            }
            lBase = 10;
            
            goto number;
            
        case 'n':
            if (lFlags & LONGINT)
            {
                *va_arg(argp, VOS_INT32*) = (VOS_INT32)(pucOutBuf-out_buf);
            }
            else if (lFlags & SHORTINT)
            {
                *va_arg(argp, VOS_INT16*) = (VOS_INT16)(pucOutBuf-out_buf);
            }
            else
            {
                *va_arg(argp, VOS_INT*) = (VOS_INT)(pucOutBuf-out_buf);
            }
            break;
        case 'O':
            lFlags |= LONGINT;
        case 'o':
            ARG(unsigned);
            lBase = 8;
            
            goto nosign;
            
        case 'p':
            ulLong = (VOS_UINT_PTR)va_arg(argp, VOS_VOID *);
            lBase = 16;
            
            goto nosign;
            
        case 's':
            if ( (pcBuf = va_arg(argp, VOS_CHAR*))==0 )
            {
                pcBuf = "(null)";
            }
            if (lPrec >= 0)
            {
                VOS_CHAR *p;

                if ((p = (VOS_CHAR *)VOS_MemChr((const VOS_CHAR *)pcBuf, 0, lPrec))!=0)
                {
                    lConverSize = p - pcBuf;
                    if (lConverSize > lPrec)
                    {
                        lConverSize = lPrec;
                    }
                 }
                 else
                 {
                    lConverSize = lPrec;
                 }
            }
            else
            {
                lConverSize = VOS_StrLen(pcBuf);
            }
            ucPrefixSign = '\0';
            
            goto pforw;
            
        case 'U':
            lFlags |= LONGINT;
        case 'u':
            ARG(unsigned);
            lBase = 10;
            
            goto nosign;
            
        case 'X':
            pucDigs = "0123456789ABCDEF";
        case 'x':
            ARG(unsigned);
            lBase = 16;
            if (lFlags & ALT && ulLong != 0)
            {
                lFlags |= HEXPREFIX;
            }

nosign:    ucPrefixSign = '\0';

number:     if ((lDprec = lPrec) >= 0)
            {
                lFlags &= ~ZEROPAD;
            }

            pcBuf = ucBuf + BUF;
            if (ulLong != 0 || lPrec != 0)
            {
                do {
                    *--pcBuf = pucDigs[ulLong % lBase];
                    ulLong /= lBase;
                } while (ulLong);
                pucDigs = "0123456789abcdef";
                if (lFlags & ALT && lBase == 8 && *pcBuf != '0')
                {
                    *--pcBuf = '0';
                }
            }
            lConverSize = ucBuf + BUF - pcBuf;

pforw:
            lFieldSize = lConverSize + lFpprec;
            if (ucPrefixSign)
            {
                lFieldSize++;
            }
            if (lFlags & HEXPREFIX)
            {
                lFieldSize += 2;
            }
            lRealSize = lDprec > lFieldSize ? lDprec : lFieldSize;

            if ((lFlags & (LADJUST|ZEROPAD)) == 0 && lFormatWidth)
            {
                for (ltemp = lRealSize; ltemp < lFormatWidth; ltemp++)
                {
                    if(ulWriteLen--)
                    {
                        *pucOutBuf++=' ';
                    }
                    else
                    {
                        return (VOS_INT32)ulStrLen;
                    }
                }
            }

            if (ucPrefixSign)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++=ucPrefixSign;
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }

            if (lFlags & HEXPREFIX)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++='0';
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
                if(ulWriteLen--)
                {
                    *pucOutBuf++=(VOS_CHAR)*pucFmt;
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }

            if ((lFlags & (LADJUST|ZEROPAD)) == ZEROPAD)
            {
                for (ltemp = lRealSize; ltemp < lFormatWidth; ltemp++)
                {
                    if(ulWriteLen--)
                    {
                        *pucOutBuf++='0';
                    }
                    else
                    {
                        return (VOS_INT32)ulStrLen;
                    }
                }
            }

            for (ltemp = lFieldSize; ltemp < lDprec; ltemp++)
            {
               if(ulWriteLen--)
               {
                  *pucOutBuf++='0';
               }
               else
               {
                   return (VOS_INT32)ulStrLen;
               }
            }

            ltemp = lConverSize;
            while (--ltemp >= 0)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++=*pcBuf++;
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }

            while (--lFpprec >= 0)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++='0';
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }

            if (lFlags & LADJUST)
            {
                for (ltemp = lRealSize; ltemp < lFormatWidth; ltemp++)
                {
                    if(ulWriteLen--)
                    {
                        *pucOutBuf++=' ';
                    }
                    else
                    {
                        return (VOS_INT32)ulStrLen;
                    }
                }
            }

            break;
        case '\0':
                        
                        goto    lvspret;
                        
        default:
                        if(ulWriteLen--)
                        {
                            *pucOutBuf++=(VOS_CHAR)*pucFmt;
                        }
                        else
                        {
                            return (VOS_INT32)ulStrLen;
                        }

            }
        }
lvspret:
        if(ulWriteLen--)
        {
            *pucOutBuf=0;
        }
        else
        {
            return (VOS_INT32)ulStrLen;
        }
        return (VOS_INT)(pucOutBuf-out_buf);
}

VOS_INT32 VOS_nvsprintf(VOS_CHAR * str, VOS_UINT32 ulMaxStrLen, const VOS_CHAR *format, va_list arguments)
{
    VOS_INT32 nc;

    if (( NULL == str ) || ( NULL == format ) || (ulMaxStrLen == 0))
    {
        return -1;
    }
    else
    {
        VOS_MemSet_s(str, ulMaxStrLen, 0, ulMaxStrLen);
    }

    nc = ANSI_nvsprintf(str, ulMaxStrLen - 1, (const VOS_CHAR *) format, arguments);

    return nc;
}

VOS_INT VOS_nvsprintf_s(VOS_CHAR * str, VOS_SIZE_T ulMaxStrLen, VOS_SIZE_T ulCount, const VOS_CHAR *format, va_list arguments)
{
    if ( ulCount > VOS_SECUREC_MEM_MAX_LEN )
    {
        return -1;
    }

    if (( NULL == str ) || ( NULL == format ) || (ulMaxStrLen == 0))
    {
        return -1;
    }
    else
    {
        VOS_MemSet_s(str, ulMaxStrLen, 0, ulMaxStrLen);
    }

    return (VOS_INT)ANSI_nvsprintf(str, (VOS_UINT32)(ulMaxStrLen - 1), (const VOS_CHAR *) format, arguments);
}

VOS_INT32 VOS_nsprintf(VOS_CHAR *str, VOS_UINT32 ulMaxStrLen, const VOS_CHAR *fmt, ...)
{
    va_list arg;
    register VOS_INT32 nc;


    if (( NULL == str ) || ( NULL == fmt ) || (ulMaxStrLen == 0))
    {
        return -1;
    }
    else
    {
        VOS_MemSet_s(str, ulMaxStrLen, 0, ulMaxStrLen);
    }

    va_start(arg, fmt);
    nc = ANSI_nvsprintf(str, ulMaxStrLen - 1, (const VOS_CHAR *) fmt, arg);
    va_end(arg);
    return (nc);
}

VOS_INT VOS_nsprintf_s(VOS_CHAR *str, VOS_SIZE_T ulMaxStrLen, VOS_SIZE_T ulCount, const VOS_CHAR *fmt, ...)
{
     va_list arg;
    register VOS_INT nc;

    if ( ulCount > VOS_SECUREC_MEM_MAX_LEN )
    {
        return -1;
    }
    
    if (( NULL == str ) || ( NULL == fmt ) || (ulMaxStrLen == 0))
    {
        return -1;
    }
    else
    {
        VOS_MemSet_s(str, ulMaxStrLen, 0, ulMaxStrLen);
    }

    va_start(arg, fmt);
    nc = (VOS_INT)ANSI_nvsprintf(str, (VOS_UINT32)(ulMaxStrLen - 1), (const VOS_CHAR *) fmt, arg);
    va_end(arg);
    return (nc);
}

VOS_PRINT_HOOK g_pfnPrintHook = VOS_NULL_PTR;

VOS_PRINT_HOOK VOS_HookPrint( VOS_PRINT_HOOK newHook )
{
    VOS_PRINT_HOOK oldHook = g_pfnPrintHook;

    g_pfnPrintHook = newHook;

    return oldHook;
}

VOS_INT32 vos_printf( const VOS_CHAR * format, ... )
{
    VOS_INT32  rc;
    VOS_UINT32 ulReturn = VOS_OK;

    va_list    argument;
    VOS_CHAR   output_info[VOS_MAX_PRINT_LEN + 4];
    va_start( argument, format );
    rc = VOS_nvsprintf( output_info, VOS_MAX_PRINT_LEN, format, argument );
    va_end( argument );
    output_info[VOS_MAX_PRINT_LEN - 1] = '\0';

    if( rc >= VOS_MAX_PRINT_LEN - 1 )
    {
        VOS_UINT32  ulTempLen;
        VOS_CHAR *  pcWarning = " [!!!Warning: Print too long!!!]\r\n";
        ulTempLen = VOS_StrLen( pcWarning );
        VOS_StrNCpy( output_info + ( VOS_MAX_PRINT_LEN - ulTempLen - 1 ), pcWarning, ulTempLen );
        VOS_SetErrorNo( VOS_ERRNO_LIB_PRINTF_INPUTFORMATTOOLONG );
        ulReturn = VOS_ERRNO_LIB_PRINTF_INPUTFORMATTOOLONG;
    }
    else if( rc < 0 )
    {
        VOS_CHAR *  pcWarning = "\r\n### vos printf error: unknown internal error. ###\r\n";
        VOS_StrCpy( output_info, pcWarning );
        VOS_SetErrorNo( VOS_ERRNO_LIB_PRINTF_UNKNOWNINTERERROR );
        ulReturn = VOS_ERRNO_LIB_PRINTF_UNKNOWNINTERERROR;
    }

    if( g_pfnPrintHook != VOS_NULL_PTR )
    {
        ulReturn = (VOS_UINT32)(*g_pfnPrintHook)( output_info );
        if( ulReturn != (VOS_UINT32)VOS_ERROR )
        {
            return (VOS_INT32)VOS_OK;
        }
    }
    printk( "%s",output_info );
    return (VOS_INT32)ulReturn;
}
