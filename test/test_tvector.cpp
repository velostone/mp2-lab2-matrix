#include "tmatrix.h"
#include <gtest.h>

template <typename T>
class TestTVector : public ::testing::Test 
{
protected: 
	TDynamicVector<T> *v1, *v2, *add, *sub, *v_test;
	T *arr_v1, *arr_v2, *arr_add, *arr_sub, *add_scal, *sub_scal, *mult_scal;
public:
	void SetUp()
	{
		arr_v1 = new T[5]{ 5, 8, 10, -15, 6 };
		arr_v2 = new T[5]{ 0, 3, -6, 8, 6 };
		arr_add = new T[5]{ 5, 11, 4, -7, 12 };
		arr_sub = new T[5]{ 5, 5, 16, -23, 0 };
		add_scal = new T[5]{ 10, 13, 15, -10, 11 };
		sub_scal = new T[5]{ 0, 3, 5, -20, 1 };
		mult_scal = new T[5]{ 10, 16, 20, -30, 12 };
		v1 = new TDynamicVector<T>(arr_v1, 5);
		v2 = new TDynamicVector<T>(arr_v2, 5);
		add = new TDynamicVector<T>(arr_add, 5);
		sub = new TDynamicVector<T>(arr_sub, 5);
	}
	void TearDown()
	{
		delete[] arr_v1;
		arr_v1 = nullptr;
		delete[] arr_v2;
		arr_v2 = nullptr;
		delete[] arr_add;
		arr_add = nullptr;
		delete[] arr_sub;
		arr_sub = nullptr;
		delete[] add_scal;
		add_scal = nullptr;
		delete[] sub_scal;
		sub_scal = nullptr;
		delete v1;
		delete v2;
		delete add;
		delete sub;
	}
	void CreateVector(size_t size = 1, size_t flag = 0)
	{
		if (flag)
			v_test = new TDynamicVector<T>(*v1);
		else v_test = new TDynamicVector<T>(size);
	}
	void CreateVectorRes(T* arr, size_t size = 1)
	{
		v_test = new TDynamicVector<T>(arr, size);
	}
};
TYPED_TEST_CASE_P(TestTVector);

TYPED_TEST_P(TestTVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(this -> CreateVector(5));
}

TYPED_TEST_P(TestTVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(this -> CreateVector(MAX_VECTOR_SIZE + 1));
}

TYPED_TEST_P(TestTVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(this -> CreateVector(-5));
}

TYPED_TEST_P(TestTVector, can_create_copied_vector)
{
  ASSERT_NO_THROW(this -> CreateVector(5, 1));
}

TYPED_TEST_P(TestTVector, copied_vector_is_equal_to_source_one)
{
	this -> CreateVector(5, 1);
	EXPECT_EQ(*v_test, *v1);
}

TYPED_TEST_P(TestTVector, copied_vector_has_its_own_memory)
{
	this -> CreateVector(5, 1);
	EXPECT_NE(v_test, v1);
}

TYPED_TEST_P(TestTVector, can_get_size)
{
  EXPECT_EQ(5, v1->size());
}

TYPED_TEST_P(TestTVector, can_set_and_get_element)
{
  EXPECT_EQ(5, v1->at(0));
}

TYPED_TEST_P(TestTVector, throws_when_set_element_with_negative_index)
{
  ASSERT_ANY_THROW(v1->at(-1) = 8);
}

TYPED_TEST_P(TestTVector, throws_when_set_element_with_too_large_index)
{
  ASSERT_ANY_THROW(v1->at(10) = 8);
}

TYPED_TEST_P(TestTVector, can_assign_vector_to_itself)
{
	*v1 = *v1;
	EXPECT_EQ(*v1, *v1);
}

TYPED_TEST_P(TestTVector, can_assign_vectors_of_equal_size)
{
	*v1 = *v2;
	EXPECT_EQ(*v1, *v2);
}

TYPED_TEST_P(TestTVector, assign_operator_change_vector_size)
{
	this -> CreateVector(10);
	*v1 = *v_test;
	EXPECT_EQ(10, v1->size());
}

TYPED_TEST_P(TestTVector, can_assign_vectors_of_different_size)
{
	this -> CreateVector(10);
	*v1 = *v_test;
	EXPECT_EQ(*v1, *v_test);
}

TYPED_TEST_P(TestTVector, compare_equal_vectors_return_true)
{
	*v1 = *v2;
	EXPECT_TRUE(*v1 == *v2);
}

TYPED_TEST_P(TestTVector, compare_vector_with_itself_return_true)
{
  EXPECT_TRUE(*v1 == *v1);
}

TYPED_TEST_P(TestTVector, vectors_with_different_size_are_not_equal)
{
	this -> CreateVector(10);
	EXPECT_FALSE(*v1 == *v_test);
}

TYPED_TEST_P(TestTVector, can_add_scalar_to_vector)
{
	this -> CreateVectorRes(add_scal, 5);
	*v1 = *v1 + 5;
	EXPECT_EQ(*v1, *v_test);
}

TYPED_TEST_P(TestTVector, can_subtract_scalar_from_vector)
{
	this -> CreateVectorRes(sub_scal, 5);
	*v1 = *v1 - 5;
	EXPECT_EQ(*v1, *v_test);
}

TYPED_TEST_P(TestTVector, can_multiply_scalar_by_vector)
{
	this -> CreateVectorRes(mult_scal, 5);
	EXPECT_EQ(*v1 * 2, *v_test);
}

TYPED_TEST_P(TestTVector, can_add_vectors_with_equal_size)
{
	EXPECT_EQ(*add, *v1 + *v2);
}

TYPED_TEST_P(TestTVector, cant_add_vectors_with_not_equal_size)
{
	this -> CreateVector(10);
	ASSERT_ANY_THROW(*v1 + *v_test);
}

TYPED_TEST_P(TestTVector, can_subtract_vectors_with_equal_size)
{
	EXPECT_EQ(*sub, *v1 - *v2);
}

TYPED_TEST_P(TestTVector, cant_subtract_vectors_with_not_equal_size)
{
	this -> CreateVector(10);
	ASSERT_ANY_THROW(*v1 - *v_test);
}

TYPED_TEST_P(TestTVector, can_multiply_vectors_with_equal_size)
{
	EXPECT_EQ(-120, *v1 * (*v2));
}

TYPED_TEST_P(TestTVector, cant_multiply_vectors_with_not_equal_size)
{
	this -> CreateVector(10);
	ASSERT_ANY_THROW(*v1 * (*v_test));
}

REGISTER_TYPED_TEST_CASE_P(TestTVector, can_create_vector_with_positive_length,
	cant_create_too_large_vector, throws_when_create_vector_with_negative_length,
	can_create_copied_vector, copied_vector_is_equal_to_source_one, copied_vector_has_its_own_memory,
	can_get_size, can_set_and_get_element, throws_when_set_element_with_negative_index,
	throws_when_set_element_with_too_large_index, can_assign_vector_to_itself,
	can_assign_vectors_of_equal_size, assign_operator_change_vector_size,
	can_assign_vectors_of_different_size, compare_equal_vectors_return_true,
	compare_vector_with_itself_return_true, vectors_with_different_size_are_not_equal,
	can_add_scalar_to_vector, can_subtract_scalar_from_vector, can_multiply_scalar_by_vector, 
	can_add_vectors_with_equal_size, cant_add_vectors_with_not_equal_size, 
	can_subtract_vectors_with_equal_size, cant_subtract_vectors_with_not_equal_size, 
	can_multiply_vectors_with_equal_size, cant_multiply_vectors_with_not_equal_size);

typedef ::testing::Types<int, float, double> TestTVectorTypes;
INSTANTIATE_TYPED_TEST_CASE_P(TestTVectorInstantiation, TestTVector, TestTVectorTypes);

