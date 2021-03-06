#include "settings.h"


Settings* parse_args(int argc, char **argv){
	Settings* s = malloc(sizeof(Settings));
	s->nSources = 0;
	s->xmax=screen_xmax();
	s->ymax=screen_ymax();
	s->udelay=0;
	s->residual=0.1;
	int aux;
	while( (aux = getopt(argc, argv, "t:m:r:")) != -1){
		switch(aux){
			case 't':
				s->udelay=atof(optarg);
				break;
			case 'm':
				if (strcmp(optarg, "center") == 0){
					s->heatSources = realloc(s->heatSources, sizeof(HeatSource*)*(s->nSources+1)); 

					int radium = min(s->xmax, s->ymax)/3;

					s->heatSources[s->nSources] = heat_new_heatsource(((int) (s->xmax/2))-radium/2, ((int) s->ymax/2)-radium/2, radium, 500);
					s->nSources++;

				}else if (strcmp(optarg, "2center") == 0){
					s->heatSources = realloc(s->heatSources, sizeof(HeatSource*)*(s->nSources+2));
					int radium = min(s->xmax, s->ymax)/3;

					s->heatSources[s->nSources] = heat_new_heatsource(((int) (s->xmax/2))-radium, ((int) s->ymax/2)-radium, radium, 500);
					s->nSources++;

					s->heatSources[s->nSources] = heat_new_heatsource(((int) (s->xmax/2))+radium/3, ((int) s->ymax/2-radium), radium, 500);
					s->nSources++;

				}else if (strcmp(optarg, "random") == 0){
					s->heatSources = realloc(s->heatSources, sizeof(HeatSource*)*(s->nSources+2));
					int radium = min(s->xmax, s->ymax)/3;

					s->heatSources[s->nSources] = heat_new_heatsource(((int) (s->xmax/2)-radium), ((int) s->ymax/2)-radium, radium, 500);
					s->nSources++;

					s->heatSources[s->nSources] = heat_new_heatsource(((int) (s->xmax/2)+radium/3), ((int) s->ymax/2-radium), radium, 500);
					s->nSources++;

					s->heatSources[s->nSources] = heat_new_heatsource(((int) s->xmax*0.2), ((int) s->ymax*0.1) , radium*2, 500);
					s->nSources++;

					s->heatSources[s->nSources] = heat_new_heatsource(((int) s->xmax-radium*3.9),((int) s->ymax-radium*3), radium*2, 500);
					s->nSources++;

				}else{
					error_exit("Error mode not recognized", 2);
				}

				break;
			case 'r':
				s->residual=atof(optarg);
				break;
			case '?':
				error_exit("Error option not recognized", 2);
		}
	}

	return s;

}
