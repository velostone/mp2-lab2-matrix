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
		this->arr_v1 = new T[5]{ 5, 8, 10, -15, 6 };
		this->arr_v2 = new T[5]{ 0, 3, -6, 8, 6 };
		this->arr_add = new T[5]{ 5, 11, 4, -7, 12 };
		this->arr_sub = new T[5]{ 5, 5, 16, -23, 0 };
		this->add_scal = new T[5]{ 10, 13, 15, -10, 11 };
		this->sub_scal = new T[5]{ 0, 3, 5, -20, 1 };
		this->mult_scal = new T[5]{ 10, 16, 20, -30, 12 };
		this->v1 = new TDynamicVector<T>(arr_v1, 5);
		this->v2 = new TDynamicVector<T>(arr_v2, 5);
		this->add = new TDynamicVector<T>(arr_add, 5);
		this->sub = new TDynamicVector<T>(arr_sub, 5);
	}
	void TearDown()
	{
		delete[] this->arr_v1;
		this->arr_v1 = nullptr;
		delete[] this->arr_v2;
		this->arr_v2 = nullptr;
		delete[] this->arr_add;
		this->arr_add = nullptr;
		delete[] this->arr_sub;
		this->arr_sub = nullptr;
		delete[] this->add_scal;
		this->add_scal = nullptr;
		delete[] this->sub_scal;
		this->sub_scal = nullptr;
		delete this->v1;
		delete this->v2;
		delete this->add;
		delete this->sub;
	}
	void CreateVector(size_t size = 1, size_t flag = 0)
	{
		if (flag)
			this->v_test = new TDynamicVector<T>(*v1);
		else this->v_test = new TDynamicVector<T>(size);
	}
	void CreateVectorRes(T* arr, size_t size = 1)
	{
		this->v_test = new TDynamicVector<T>(arr, size);
	}
};

typedef ::testing::Types<int, float, double> types;

TYPED_TEST_CASE(TestTVector, types);

TYPED_TEST(TestTVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(this -> CreateVector(5));
}

TYPED_TEST(TestTVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(this -> CreateVector(MAX_VECTOR_SIZE + 1));
}

TYPED_TEST(TestTVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(this -> CreateVector(-5));
}

TYPED_TEST(TestTVector, can_create_copied_vector)
{
  ASSERT_NO_THROW(this -> CreateVector(5, 1));
}

TYPED_TEST(TestTVector, copied_vector_is_equal_to_source_one)
{
	this -> CreateVector(5, 1);
	EXPECT_EQ(*(this -> v_test), *(this -> v1));
}

TYPED_TEST(TestTVector, copied_vector_has_its_own_memory)
{
	this -> CreateVector(5, 1);
	EXPECT_NE(this->v_test, this->v1);
}

TYPED_TEST(TestTVector, can_get_size)
{
  EXPECT_EQ(5, this->v1->size());
}

TYPED_TEST(TestTVector, can_set_and_get_element)
{
  EXPECT_EQ(5, this->v1->at(0));
}

TYPED_TEST(TestTVector, throws_when_set_element_with_negative_index)
{
  ASSERT_ANY_THROW(this->v1->at(-1) = 8);
}

TYPED_TEST(TestTVector, throws_when_set_element_with_too_large_index)
{
  ASSERT_ANY_THROW(this->v1->at(10) = 8);
}

TYPED_TEST(TestTVector, can_assign_vector_to_itself)
{
	*(this->v1) = *(this->v1);
	EXPECT_EQ(*(this -> v1), *(this -> v1));
}

TYPED_TEST(TestTVector, can_assign_vectors_of_equal_size)
{
	*(this->v1) = *(this->v2);
	EXPECT_EQ(*(this -> v1), *(this -> v2));
}

TYPED_TEST(TestTVector, assign_operator_change_vector_size)
{
	this -> CreateVector(10);
	*(this->v1) = *(this->v_test);
	EXPECT_EQ(10, this->v1->size());
}

TYPED_TEST(TestTVector, can_assign_vectors_of_different_size)
{
	this -> CreateVector(10);
	*(this->v1) = *(this->v_test);
	EXPECT_EQ(*(this->v1), *(this->v_test));
}

TYPED_TEST(TestTVector, compare_equal_vectors_return_true)
{
	*(this->v1) = *(this->v2);
	EXPECT_TRUE(*(this->v1) == *(this->v2));
}

TYPED_TEST(TestTVector, compare_vector_with_itself_return_true)
{
  EXPECT_TRUE(*(this->v1) == *(this->v1));
}

TYPED_TEST(TestTVector, vectors_with_different_size_are_not_equal)
{
	this -> CreateVector(10);
	EXPECT_FALSE(*(this->v1) == *(this->v_test));
}

TYPED_TEST(TestTVector, can_add_scalar_to_vector)
{
	this -> CreateVectorRes(this->add_scal, 5);
	*(this->v1) = *(this->v1) + 5;
	EXPECT_EQ(*(this->v1), *(this->v_test));
}

TYPED_TEST(TestTVector, can_subtract_scalar_from_vector)
{
	this -> CreateVectorRes(this->sub_scal, 5);
	*(this->v1) = *(this->v1) - 5;
	EXPECT_EQ(*(this->v1), *(this->v_test));
}

TYPED_TEST(TestTVector, can_multiply_scalar_by_vector)
{
	this -> CreateVectorRes(this->mult_scal, 5);
	EXPECT_EQ(*(this->v1) * 2, *(this->v_test));
}

TYPED_TEST(TestTVector, can_add_vectors_with_equal_size)
{
	EXPECT_EQ(*(this->add), *(this->v1) + *(this->v2));
}

TYPED_TEST(TestTVector, cant_add_vectors_with_not_equal_size)
{
	this -> CreateVector(10);
	ASSERT_ANY_THROW(*(this->v1) + *(this->v_test));
}

TYPED_TEST(TestTVector, can_subtract_vectors_with_equal_size)
{
	EXPECT_EQ(*(this->sub), *(this->v1) - *(this->v2));
}

TYPED_TEST(TestTVector, cant_subtract_vectors_with_not_equal_size)
{
	this -> CreateVector(10);
	ASSERT_ANY_THROW(*(this->v1) - *(this->v_test));
}

TYPED_TEST(TestTVector, can_multiply_vectors_with_equal_size)
{
	EXPECT_EQ(-120, *(this->v1) * *(this->v2));
}

TYPED_TEST(TestTVector, cant_multiply_vectors_with_not_equal_size)
{
	this -> CreateVector(10);
	ASSERT_ANY_THROW(*(this->v1) * *(this->v_test));
}



