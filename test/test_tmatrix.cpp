#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(5);
	m[0][0] = 1;
	TDynamicMatrix<int> mcpy(m);

  EXPECT_EQ(m, mcpy);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> mcpy(m);

  EXPECT_NE(&m[0], &mcpy[0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);

	EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);

	m[0][0] = 1;

	EXPECT_EQ(1, m[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	int* arr = new int[5] { 1, 1, 1, 1, 1 };
	TDynamicVector<int> v(arr, 5);
	delete[] arr;

	ASSERT_ANY_THROW(m.at(5) = v);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	int* arr = new int[5] { 1, 1, 1, 1, 1 };
	TDynamicVector<int> v(arr, 5);
	delete[] arr;

  ASSERT_ANY_THROW(m.at(5) = v);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);
	m2[0][0] = 1;

	m1 = m2;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(3);

	m1 = m2;

	EXPECT_EQ(3, m1.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(3);

	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);
	m1[0][0] = 1;
	m2[0][0] = 1;

	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(5);

	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(3);

	EXPECT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);
	m1[0][0] = 1;
	m1[1][1] = 1;

	m2 = m1 + m2;

	EXPECT_EQ(m1, m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(3);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);
	TDynamicMatrix<int> res(5);
	m2[0][0] = 1;
	m2[1][1] = 1;
	res[0][0] = -1;
	res[1][1] = -1;

	m1 = m1 - m2;

	EXPECT_EQ(res, m1);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(3);

	ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_scalar)
{
	TDynamicMatrix<int> m(5);
	int* arr = new int[5] { 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(arr, 5);
	delete[] arr;
	m[0] = v;
	TDynamicMatrix<int> res(5);
	res[0] = v * 5;
	
	EXPECT_EQ(res, m * 5);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_vector_equal_size)
{
	TDynamicMatrix<int> m(5);
	int* arr1 = new int[5] { 1, 2, 3, 4, 5 };
	int* arr2 = new int[5] { 1, 0, 0, 1, 1 };
	TDynamicVector<int> v1(arr1, 5);
	TDynamicVector<int> v2(arr2, 5);
	delete[] arr1;
	delete[] arr2;
	m[0] = v1;
	TDynamicVector<int> res(5);
	res[0] = 10;
	
	EXPECT_EQ(res, m * v2);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_vector_not_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicVector<int> v(3);
	
	ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);
	int* arr1 = new int[5] { 2, 2, 3, 4, 5 };
	int* arr2 = new int[5] { 1, 0, 0, 1, 1 };
	TDynamicVector<int> v1(arr1, 5);
	TDynamicVector<int> v2(arr2, 5);
	delete[] arr1;
	delete[] arr2;
	m1[0] = v1;
	m2[0] = v2;
	TDynamicMatrix<int> res(5);
	res[0] = v2 * 2;
	
	EXPECT_EQ(res, m1 * m2);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(3);

	ASSERT_ANY_THROW(m1 * m2);
}