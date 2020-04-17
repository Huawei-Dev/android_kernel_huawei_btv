#ifndef _HISI_DEVFREQ_H
#define _HISI_DEVFREQ_H

struct hisi_devfreq_data {
	int vsync_hit;
	int cl_boost;
};

#ifdef CONFIG_DEVFREQ_GOV_GPU_SCENE_AWARE
#define GPU_DEFAULT_GOVERNOR	"gpu_scene_aware"
#else
#define GPU_DEFAULT_GOVERNOR	"mali_ondemand"
#endif

int hisi_devfreq_free_freq_table(struct device *dev, unsigned int **table);

int hisi_devfreq_init_freq_table(struct device *dev, unsigned int **table);

#endif /* _HISI_DEVFREQ_H */
