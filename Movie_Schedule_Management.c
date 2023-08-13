#include "rate_and_sort.h"
#include "headers_and_macros.h"
#include "fill_slots.h"


int main(int argc, char *argv[])
{
	printf("\033[0m");
	char choice = 'Y', alloted[MAXSCREENS][MAXSLOTS][MAXNAME], hol;
	int i=-1, j, k, n_movies, n_screens, n_slots;
	Movie movie_list[MAXMOVIES];
	FILE *fptr = fopen(argv[1], "w");
  
	printf("\n******************************** WELCOME TO MOVIE SCHEDULING SYSTEM ********************************\n");

	printf("\n\nEnter number of screens: ");  scanf("%d", &n_screens);

	while (toupper(choice) == 'Y')
	{
		i++;
		printf("Enter 'n' for new movie and 'o' for old movie: ");
		do
		{
			scanf(" %c", &movie_list[i].oldnew);
			if (movie_list[i].oldnew != 'o' && movie_list[i].oldnew != 'n' && movie_list[i].oldnew != 'O' && movie_list[i].oldnew != 'N')
				printf("Invalid input. Please enter again: ");
		} while (movie_list[i].oldnew != 'o' && movie_list[i].oldnew != 'n' && movie_list[i].oldnew != 'O' && movie_list[i].oldnew != 'N');

		printf("Enter the movie name, demand score(1-10) of movie %d: ", i + 1);	scanf("%s", movie_list[i].name);

		do
		{
			scanf(" %f", &movie_list[i].d_score);
			if (movie_list[i].d_score < 1 || movie_list[i].d_score > 10)
				printf("Invalid demand score. Please enter again: ");
		} while (movie_list[i].d_score < 1 || movie_list[i].d_score > 10);

		if (toupper(movie_list[i].oldnew) == 'O')
		{
			printf("Enter success rate:");
			do
			{
				scanf("%f", &movie_list[i].s_rate);
				if (movie_list[i].s_rate < 1 || movie_list[i].s_rate > 10)
					printf("Invalid success rate. Please enter again: ");
			} while (movie_list[i].s_rate < 1 || movie_list[i].s_rate > 10);
	    	}
	
		movieRating(movie_list, i);

		printf("\nDo you want to Enter more movies?(y/n): "); scanf(" %c", &choice);

		while(tolower(choice)!='y' && tolower(choice)!='n'){
			printf("Invalid choice. Please enter again: "); scanf(" %c", &choice);
		}
		printf("\n----------------------------------------------------------------------------------------------------\n");
	}
  	n_movies = i + 1;

	sortByRating(movie_list, n_movies);

	printf("\nMOVIE NAME\tRATING\n");
	for (i = 0; i < n_movies; i++)	printf("%s\t%.2f\n", movie_list[i].name, movie_list[i].rating);

  	for (k = 0; k < 3; k++) {
    		printf("\033[1;35m");
   		switch(k)
   		{
      			case 0:
       				printf("\nFRIDAY\n"); fprintf(fptr, "FRIDAY");	break;
      			case 1:
				printf("\nSATURDAY\n"); fprintf(fptr, "SATURDAY");	break;
     			case 2:
       				printf("\nSUNDAY\n"); fprintf(fptr, "SUNDAY");	break;
    		}
		printf("\033[0m");
		printf("Enter 'y' for holiday and 'n' for working day: "); 
    
		do {
			scanf(" %c",&hol);
			if (hol != 'y' && hol != 'Y' && hol != 'n' && hol != 'N')
				printf("Invalid input. Please enter again: ");
		} while (hol!= 'n' && hol != 'N' && hol != 'y' && hol!= 'Y');
    
		n_slots = (hol == 'y')? 6: 4;

		slots_per_movie(movie_list, n_slots, n_screens, n_movies);
		initialise(alloted, n_screens, n_slots);
		allotMovies(movie_list, n_movies, alloted, n_screens, n_slots);

		fillEmpty(movie_list, n_movies, n_screens, n_slots, alloted);

		printf("\n----------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "\n----------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("\033[1;36m");

		(hol == 'y')? printf("Screens\t6:30-9:00\t9:30-12:00\t12:30-15:00\t15:30-18:00\t18:30-21:00\t21:30-24:00") : printf("Screens\t9:00-11:30\t13:00-15:30\t17:00-19:30\t20:00-22:30") ;
		(hol == 'y')? fprintf(fptr, "Screens\t6:30-9:00\t9:30-12:00\t12:30-15:00\t15:30-18:00\t18:30-21:00\t21:30-24:00") : fprintf(fptr, "Screens\t9:00-11:30\t13:00-15:30\t17:00-19:30\t20:00-22:30") ; 

		printf("\033[0m");
		printf("\n----------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "\n----------------------------------------------------------------------------------------------------------------------------------------\n");

		for (i = 0; i < n_screens; i++) {
			printf("\033[1;36m");
			printf("Screen %d ", i + 1);	fprintf(fptr, "Screen %d ", i + 1);
			printf("\033[0m"); printf("| ");	fprintf(fptr, "| ");
    
			for (j = 0; j < n_slots; j++){
				printf("\033[1;33m");
				printf("%s ", alloted[i][j]); fprintf(fptr, "%s ", alloted[i][j]);
				printf("\033[0m"); printf("| ");	fprintf(fptr, "| ");
			}
			printf("\n");	fprintf(fptr, "\n");
		}

		printf("\033[0m");
		printf("----------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "----------------------------------------------------------------------------------------------------------------------------------------\n\n");

	}

	printf("Enter new success rate:\n");
	for (i = 0; i < n_movies; i++) {
		if (movie_list[i].oldnew == 'n' || movie_list[i].oldnew == 'N') {
			movie_list[i].oldnew = 'o';
		}
		printf("%s :", movie_list[i].name);
    		do {
			scanf("%f", &movie_list[i].s_rate);
			if (movie_list[i].s_rate < 1 || movie_list[i].s_rate > 10)
				printf("Invalid success rate. Please enter again: ");
		} while (movie_list[i].s_rate < 1 || movie_list[i].s_rate > 10);

		movieRating(movie_list, i);
	}

	sortByRating(movie_list, n_movies);
	printf("\nMOVIE NAME\tRATING\n");
	for (i = 0; i < n_movies; i++)	printf("%s\t%.2f\n", movie_list[i].name, movie_list[i].rating);

	for (k = 3; k < 7; k++) {
		printf("\033[1;35m");
		switch(k)
		{
			case 3:
				printf("\nMONDAY\n"); fprintf(fptr, "MONDAY");	break;
			case 4:
				printf("\nTUESDAY\n"); fprintf(fptr, "TUESDAY");	break;
			case 5:
				printf("\nWEDNESDAY\n"); fprintf(fptr, "WEDNESDAY");	break;
			case 6:
				printf("\nTHURSDAY\n"); fprintf(fptr, "THURSDAY");	break;
    		}
		printf("\033[0m");

		printf("Holiday or not? y- holiday n- not a holiday: ");

		do {
			scanf(" %c",&hol);
			if (hol != 'y' && hol != 'Y' && hol != 'n' && hol != 'N')
				printf("Invalid input. Please enter again: ");
			} while (hol!= 'n' && hol != 'N' && hol != 'y' && hol!= 'Y');
			n_slots = (hol == 'y')? 6: 4;

			 if (k==3)
			{
				n_movies = MoviesOut(n_movies);
				printf("new n_movies : %d\n", n_movies);
			}
		
		slots_per_movie(movie_list, n_slots, n_screens, n_movies);
		initialise(alloted, n_screens, n_slots);
		allotMovies(movie_list, n_movies, alloted, n_screens, n_slots);
		fillEmpty(movie_list, n_movies, n_screens, n_slots, alloted);


		printf("\n----------------------------------------------------------------------------------------------------\n");
		printf("\033[1;36m");
		fprintf(fptr, "\n----------------------------------------------------------------------------------------------------------------------------------------\n");

		(hol == 'y')? printf("Screens\t6:30-9:00\t9:30-12:00\t12:30-15:00\t15:30-18:00\t18:30-21:00\t21:30-24:00") : printf("Screens\t9:00-11:30\t13:00-15:30\t17:00-19:30\t20:00-22:30") ;
		(hol == 'y')? fprintf(fptr, "Screens\t6:30-9:00\t9:30-12:00\t12:30-15:00\t15:30-18:00\t18:30-21:00\t21:30-24:00") : fprintf(fptr, "Screens\t9:00-11:30\t13:00-15:30\t17:00-19:30\t20:00-22:30") ; 
		
		printf("\033[0m");
		printf("\n----------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "\n----------------------------------------------------------------------------------------------------------------------------------------\n");

		for (i = 0; i < n_screens; i++) {
			printf("\033[1;36m");
			printf("Screen %d ", i + 1);	fprintf(fptr, "Screen %d ", i + 1);
			printf("\033[0m"); printf("| ");	fprintf(fptr, "| ");
    
			for (j = 0; j < n_slots; j++){
				printf("\033[1;33m");
				printf("%s ", alloted[i][j]); fprintf(fptr, "%s ", alloted[i][j]);
				printf("\033[0m"); printf("| ");	fprintf(fptr, "| ");
			}
			printf("\n");	fprintf(fptr, "\n");
  		}

		printf("\033[0m");
		printf("----------------------------------------------------------------------------------------------------\n");
		fprintf(fptr, "----------------------------------------------------------------------------------------------------------------------------------------\n\n");

	}

	return 0;
}
