all:
	# g++ -std=c++11 -Wall -o course_schedule_2 course_schedule_2.cpp 
	# ./course_schedule_2
	# g++ -std=c++11 -Wall -o different_way_to_add_parens different_way_to_add_parens.cpp 
	# ./different_way_to_add_parens
	# g++ -std=c++11 -Wall -o lru_cache lru_cache.cpp 
	# ./lru_cache
	g++ -O3 -g3 -std=c++11 -Wall -o nqueens nqueens.cpp 
	eval time ./nqueens
