#include "headers_and_macros.h"

typedef struct movie_details {
	char name[MAXNAME];
	float d_score;
	float s_rate;
	float rating;
	char oldnew;
	int n_slots_per_movie;
} Movie;

void movieRating(Movie movie_list[], int i);
void sortByRating(Movie movie_list[], int n_movies) ;

void sortByRating(Movie movie_list[], int n_movies) {
  int i = 0, j = 0;
  Movie temp;
  for (i = 0; i < n_movies; i++) {
    for (j = 0; j < n_movies - i - 1; j++) {
      if (movie_list[j].rating < movie_list[j + 1].rating) {
        temp = movie_list[j];
        movie_list[j] = movie_list[j + 1];
        movie_list[j + 1] = temp;
      }
    }
  }
  return;
}


void movieRating(Movie movie_list[], int i) {
  if (toupper(movie_list[i].oldnew) == 'O') {
    movie_list[i].rating =
        (0.3 * movie_list[i].d_score) + (0.7 * movie_list[i].s_rate);
  }

  if (toupper(movie_list[i].oldnew) == 'N') {
    movie_list[i].rating = movie_list[i].d_score;
  }
  printf("Rating: %.2f\n", movie_list[i].rating);
  return;
}
