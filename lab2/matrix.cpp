#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cfloat>
#include <array>

#define N 5
#define FIELD_WIDTH 10
#define PRECISION 8
#define MIN_VALUE 0
#define MAX_VALUE 100
#define PRINT(func) \
    std::cout << std::left << std::setw(FIELD_WIDTH) << #func <<" = " << (func) << '\n'

#define PRINT_N( arr) \
    do { \
        std::cout << std::left << #arr << '\n'; \
        for (int i = 0; i < N; i++) { \
            std::cout << std::left << (arr)[i] << " "; \
        } \
        std::cout << std::endl; \
    } while (0)
	

float min_value(float matrix[N][N]) {
    float min_value = FLT_MAX;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] < min_value) {
                min_value = matrix[i][j];
            }
        }
    }
    return min_value;
}

float max_value(float matrix[N][N]) {
    float max_value = -FLT_MAX;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] > max_value) {
                max_value = matrix[i][j];
            }
        }
    }
    return max_value;
}

float max_upper_triangular_part(float matrix[N][N]){
	float max_value = -FLT_MAX;
	for (int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			if(j>=i && matrix[i][j] > max_value){
				max_value = matrix[i][j];
			}
		}
	}
	return max_value;
}

float min_upper_triangular_part(float matrix[N][N]){
	float min_value = FLT_MAX;
	for (int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			if(j>=i && matrix[i][j] < min_value){
				min_value = matrix[i][j];
			}
		}
	}
	return min_value;
}

float max_lower_triangular_part(float matrix[N][N]){
	float max_value = -FLT_MAX;
	for (int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			if(j<=i && matrix[i][j] > max_value){
				max_value = matrix[i][j];
			}
		}
	}
	return max_value;
}

float min_lower_triangular_part(float matrix[N][N]){
	float min_value = FLT_MAX;
	for (int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			if(j<=i && matrix[i][j] < min_value){
				min_value = matrix[i][j];
			}
		}
	}
	return min_value;
}

float min_main_diagonal(float matrix[N][N]){
	float min_value = FLT_MAX;
	for (int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			if(j==i && matrix[i][j] < min_value){
				min_value = matrix[i][j];
			}
		}
	}
	return min_value;
}

float max_main_diagonal(float matrix[N][N]){
	float max_value = -FLT_MAX;
	for (int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			if(j==i && matrix[i][j] > max_value){
				max_value = matrix[i][j];
			}
		}
	}
	return max_value;
}

float min_secondary_diagonal(float matrix[N][N]){
	float min_value = FLT_MAX;
	int j = 0;
	for(int i = N-1; i>=0; i--){
		if(matrix[i][j] < min_value){
			min_value = matrix[i][j];
		}
		j++;
	}
	return min_value;
}

float max_secondary_diagonal(float matrix[N][N]){
	float max_value = -FLT_MAX;
	int j = 0;
	for(int i=N-1; i>=0; i--){
		if(matrix[i][j] > max_value){
			max_value = matrix[i][j];
		}
		j++;
	}
	return max_value;
}

float mean(float matrix[N][N]){
	float count = (float)N*N;
	float sum = 0.0;
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			sum += matrix[i][j];
		}
	}
	return sum/count;
}

float mean_upper_triangular_part(float matrix[N][N]){
	int count = 0;
	float sum = 0.;
	for (int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			if(j>=i){
				count++;
				sum += matrix[i][j];
			}
		}
	}
	return sum/(float)count;
}

float mean_lower_triangular_part(float matrix[N][N]){
	int count = 0;
	float sum = 0;

	for (int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			if(j<=i){
				sum += matrix[i][j];
				count++;
			}
		}
	}
	return sum/(float)count;
}

std::array<float, N> sum_rows(float matrix[N][N]){
	std::array<float, N> sums{};
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			sums[i] += matrix[i][j];
		}
	}
	return sums;
}

std::array<float, N> sum_columns(float matrix[N][N]){
	std::array<float, N> sums{};
	for(int j=0; j<N; j++){
		for(int i=0; i<N; i++){
			sums[j] += matrix[i][j];
		}
	}
	return sums;
}

std::array<float, N> min_rows(float matrix[N][N]){
	std::array<float, N> minimums{};
	for(int i=0; i<N; i++){
		float min_value = FLT_MAX;
		for(int j=0; j<N; j++){
			if(matrix[i][j] < min_value){
				min_value = matrix[i][j];
			}
		}
		minimums[i] = min_value;
	}
	return minimums;
}

std::array<float, N> max_rows(float matrix[N][N]){
	std::array<float, N> maximums{};
	for(int i=0; i<N; i++){
		float max_value = -FLT_MAX;
		for(int j=0; j<N; j++){
			if(matrix[i][j] > max_value){
				max_value = matrix[i][j];
			}
		}
		maximums[i] = max_value;
	}
	return maximums;
}


std::array<float, N> min_columns(float matrix[N][N]){
	std::array<float, N> minimums{};
	for(int j=0; j<N; j++){
		float min_value = FLT_MAX;
		for(int i=0; i<N; i++){
			 if(matrix[i][j] < min_value){
			 	min_value = matrix[i][j];
			}
		}
		minimums[j] = min_value;
	}
	return minimums;
}

std::array<float, N> max_columns(float matrix[N][N]){
	std::array<float, N> maximums{};
	for(int j=0; j<N; j++){
		float max_value = -FLT_MAX;
		for(int i=0; i<N; i++){
			 if(matrix[i][j] > max_value){
			 	max_value = matrix[i][j];
			}
		}
		maximums[j] = max_value;
	}
	return maximums;
}

std::array<float, N> mean_rows(float matrix[N][N]){
	std::array<float, N> sums = sum_rows(matrix);
	std::array<float, N> mean{};
	for(int i=0; i<N; i++){
		mean[i] = sums[i]/(float)N;
	}
	return mean;
}

std::array<float, N> mean_columns(float matrix[N][N]){
	std::array<float, N> sums = sum_columns(matrix);
	std::array<float, N> mean{};
	for(int j=0; j<N; j++){
		mean[j] = sums[j]/(float)N;
	}
	return mean;
}

float sum_upper_triangular_part(float matrix[N][N]){
	float sum = 0.;
	for (int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			if(j>=i){
				sum += matrix[i][j];
			}
		}
	}
	return sum;
}

float sum_lower_triangular_part(float matrix[N][N]){
	float sum = 0;
	for (int i = 0; i<N; i++){
		for(int j = 0; j<N; j++){
			if(j<=i){
				sum += matrix[i][j];
			}
		}
	}
	return sum;
}

float aproximation_mean_value_element(float matrix[N][N]){
  float mean_value = mean(matrix);
  float min_diff = FLT_MAX;
  float diff;
  float value;
  for(int i=0; i<N; i++){
	for(int j=0; j<N; j++){
		diff =  std::abs(mean_value - matrix[i][j]);
		if(diff<min_diff){
			value = matrix[i][j];
			min_diff = diff;
			}
		}
	}
  return value;
}


int main() {
    float matrix[N][N];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = MIN_VALUE + (MAX_VALUE - MIN_VALUE) * (rand() / (double)RAND_MAX);
        }
    }

    std::cout << std::setprecision(PRECISION);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << std::setw(10) << matrix[i][j] << " | ";
        }
        std::cout << std::endl<<std::endl;
    }

    PRINT(min_value(matrix));
    PRINT(max_value(matrix));
    PRINT(max_upper_triangular_part(matrix));
    PRINT(max_lower_triangular_part(matrix));
    PRINT(min_upper_triangular_part(matrix));
    PRINT(min_lower_triangular_part(matrix));
    PRINT(min_main_diagonal(matrix));
    PRINT(max_main_diagonal(matrix));
    PRINT(min_secondary_diagonal(matrix));
    PRINT(max_secondary_diagonal(matrix));
    PRINT(mean(matrix));
    PRINT(mean_upper_triangular_part(matrix));
    PRINT(mean_lower_triangular_part(matrix));

    PRINT_N(sum_rows(matrix));
    PRINT_N(sum_columns(matrix));
    PRINT_N(min_rows(matrix));
    PRINT_N(min_columns(matrix));
    PRINT_N(max_rows(matrix));
    PRINT_N(max_columns(matrix));
    PRINT_N(mean_rows(matrix));
    PRINT_N(mean_columns(matrix));

    PRINT(sum_upper_triangular_part(matrix));
    PRINT(sum_lower_triangular_part(matrix));
    PRINT(aproximation_mean_value_element(matrix));
    return 0;
}
