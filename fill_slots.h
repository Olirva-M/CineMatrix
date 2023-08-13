void allotMovies(Movie movie_list[], int n_movies,char alloted[][MAXSLOTS][MAXNAME], int n_screens, int n_slots);
void slots_per_movie(Movie movie_list[], int n_slots, int n_screens,int n_movies);
void initialise(char alloted[][MAXSLOTS][MAXNAME], int n_screens, int n_slots);
void fillEmpty(Movie movie_list[], int n_movies, int n_screens, int n_slots, char alloted[][MAXSLOTS][MAXNAME]);



void allotMovies(Movie movie_list[], int n_movies,
                 char alloted[][MAXSLOTS][MAXNAME], int n_screens,
                 int n_slots) {

  int i, j, l, k, a, b, flag, temp, row, col, same_rating_count, high_count = 0, priority[n_screens][n_slots], pri_hol[] = {3,1, 2, 4, 5,6}, pri_n_hol[]={1,2,4,3}, high, pos, pri[MAXSLOTS];

  for (i=0;i<n_slots;i++)
  {
      if (n_slots == 6)  pri[i] = pri_hol[i];
      else  pri[i] = pri_n_hol[i];
  }
  high = pri[0];
  for (i = 0; i < n_slots; i++) {
    if (pri[i] > high) {
      high = pri[i];
      pos = i;
    }
  }

  for (i = 0; i < n_screens; i++) {
    for (j = 0; j < n_slots; j++) {
      priority[i][j] = pri[j];
    }
  }
  pri[pos] = 0;

  for (i = 0; i < n_movies;) {

    // Count movies that have same rating
    same_rating_count = 0;
    for (j = i; j < n_movies; j++) {
      if (movie_list[i].rating == movie_list[j].rating)
        same_rating_count++;
    }
    if (same_rating_count == 0)
      same_rating_count++;

    for (k = 0; k < movie_list[i].n_slots_per_movie; k++) {

      for (l = i; l < i + same_rating_count; l++) {

        if (high_count == n_screens) {
          for (j = 0; j < n_slots; j++) {
            if (pri[j] == high - 1) {
              high = pri[j];
              temp = j;
              break;
            }
          }
          pri[temp] = 0;
          high_count = 0;
        }

        high_count++;
        flag = 0;

        for (a = 0; a < n_screens; a++) {
          for (b = 0; b < n_slots; b++) {
            if (priority[a][b] == high && flag != 1) {
              priority[a][b] = 0;
              row = a;
              col = b;
              flag = 1;
              break;
            }
          }
        }

        strcpy((alloted[row][col]), (movie_list[l].name));
      }
    }
    i += same_rating_count;
  }

  return;
}


void slots_per_movie(Movie movie_list[], int n_slots, int n_screens,
                     int n_movies) {
  int half =  n_movies/2, i, slots=((n_screens * n_slots) / n_movies);


  for (i=0; i<half; i++)
	{
	    movie_list[i].n_slots_per_movie=slots+1;
		printf("Number of slots for %s : %d\n",movie_list[i].name,movie_list[i].n_slots_per_movie);
	}
  for (i=half; i<n_movies; i++)
	{
	    movie_list[i].n_slots_per_movie=slots-1;
		printf("Number of slots for %s : %d\n",movie_list[i].name,movie_list[i].n_slots_per_movie);
	}
    return;
}


void initialise(char alloted[][MAXSLOTS][MAXNAME], int n_screens, int n_slots) {
  int i, j;
  for (i = 0; i < n_screens; i++) {
    for (j = 0; j < n_slots; j++) {
      strcpy(alloted[i][j], "---");
    }
  }
}


void fillEmpty(Movie movie_list[], int n_movies, int n_screens, int n_slots, char alloted[][MAXSLOTS][MAXNAME] )
{
	int i, j, k=0;
	char temp[MAXNAME]="";
	for (i = 0; i < n_screens; i++) {
		for (j=0;j<n_slots;j++)
		{
			strcpy(temp,"");
			if (strcmp( alloted[i][j] , "---")==0)
			{
				strcat(temp,"*");
				strcat(temp,movie_list[k++].name);
				strcpy(alloted[i][j], temp);
			}
		}
		
	}

	return;
}