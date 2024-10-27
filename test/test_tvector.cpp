#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(10);
	v[0] = 1;
	TDynamicVector<int> vcpy(v);

  EXPECT_EQ(v, vcpy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(10);
	TDynamicVector<int> vcpy(v);
	
  EXPECT_NE(&v, &vcpy);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(10);

  ASSERT_ANY_THROW(v.at(-1) = 8);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(10);

  ASSERT_ANY_THROW(v.at(10) = 8);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(10);
	v[0] = 1;
	TDynamicVector<int> vcpy(v);
	
	v = v;

  EXPECT_EQ(v, vcpy);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(10);
	v2[0] = 3;

	v1 = v2;

  EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(5);

	v1 = v2;

  EXPECT_EQ(5, v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(5);
	v2[4] = 8;

	v1 = v2;

  EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(10);
	v1[3] = 8;
	v2[3] = 8;

  EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(10);
	v[3] = 8;

  EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(10);
	TDynamicVector<int> v2(5);

  EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> res(5);
	for (size_t i = 0; i < 5; i++)
		res[i] = 5;
	// res = (5, 5, 5, 5, 5)

	v = v + 5;
	// v = (5, 5, 5, 5, 5)

  EXPECT_EQ(v, res);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> res(5);
	for (size_t i = 0; i < 5; i++)
		res[i] = -5;
	// res = (-5, -5, -5, -5, -5)

	v = v - 5;
	// v = (-5, -5, -5, -5, -5)

	EXPECT_EQ(v, res);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(5);
	TDynamicVector<int> res(5);
	for (size_t i = 0; i < 5; i++)
		res[i] = 10;
	// res = (10, 10, 10, 10, 10)
	for (size_t i = 0; i < 5; i++)
		v[i] = 5;
	// v = (5, 5, 5, 5, 5)

	v = v * 2;
	// v = (10, 10, 10, 10, 10)

	EXPECT_EQ(v, res);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	for (size_t i = 0; i < 5; i++)
		v1[i] = 10;
	// v1 = (10, 10, 10, 10, 10)
	for (size_t i = 0; i < 3; i++)
		v2[i] = 5;
	// v2 = (5, 5, 5, 0, 0)
	TDynamicVector<int> res(5);
	res[0] = 15;
	res[1] = 15;
	res[2] = 15;
	res[3] = 10;
	res[4] = 10;
	// res = (15, 15, 15, 10, 10)

	v2 = v1 + v2;
	// v2 = (15, 15, 15, 10, 10)

	EXPECT_EQ(res, v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	for (size_t i = 0; i < 5; i++)
		v1[i] = 10;
	// v1 = (10, 10, 10, 10, 10)
	for (size_t i = 0; i < 3; i++)
		v2[i] = 5;
	// v2 = (5, 5, 5, 0, 0)
	TDynamicVector<int> res(5);
	res[0] = 5;
	res[1] = 5;
	res[2] = 5;
	res[3] = 10;
	res[4] = 10;
	// res = (5, 5, 5, 10, 10)

	v1 = v1 - v2;
	// v1 = (5, 5, 5, 10, 10)

	EXPECT_EQ(res, v1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);
	
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(5);
	v1[0] = 5;
	v1[4] = 8;
	// v1 = (5, 0, 0, 0, 8)
	v2[0] = 4;
	v2[3] = 7;
	v2[4] = 1;
	// v2 = (4, 0, 0, 7, 1)

	EXPECT_EQ(28, v1*v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(10);

	ASSERT_ANY_THROW(v1 * v2);
}

