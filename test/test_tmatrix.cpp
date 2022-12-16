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
	TDynamicMatrix<int> source_one(5);
	source_one.set_rand_matrix();
	TDynamicMatrix<int> copied(source_one);
	EXPECT_EQ(source_one, copied);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> source_one(2);
	TDynamicMatrix<int> copied(source_one);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			source_one[i][j] = 1;

	EXPECT_EQ(0, copied[0][0]);
	EXPECT_EQ(0, copied[0][1]);
	EXPECT_EQ(0, copied[1][0]);
	EXPECT_EQ(0, copied[1][1]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	EXPECT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(m[0][0] = 1);
	EXPECT_EQ(m[0][0], 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(-1, 0) = 1);
	ASSERT_ANY_THROW(m.at(0, -1) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	ASSERT_ANY_THROW(m.at(MAX_MATRIX_SIZE, 0) = 1);
	ASSERT_ANY_THROW(m.at(0, MAX_MATRIX_SIZE) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1.set_rand_matrix();
	ASSERT_NO_THROW(m2 = m1);
	EXPECT_EQ(m1[0][0], m2[0][0]);
	EXPECT_EQ(m1[0][1], m2[0][1]);
	EXPECT_EQ(m1[1][0], m2[1][0]);
	EXPECT_EQ(m1[1][1], m2[1][1]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(5), m2(2);
	m2 = m1;
	EXPECT_EQ(5, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(2), m2(5);
	m1.set_rand_matrix();
	ASSERT_NO_THROW(m2 = m1);
	EXPECT_EQ(m1[0][0], m2[0][0]);
	EXPECT_EQ(m1[0][1], m2[0][1]);
	EXPECT_EQ(m1[1][0], m2[1][0]);
	EXPECT_EQ(m1[1][1], m2[1][1]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(2), m2(5);
	m1.set_rand_matrix();
	m2 = m1;
	EXPECT_EQ(1, m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(5);
	m.set_rand_matrix();
	EXPECT_EQ(1, m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(2), m2(5);
	EXPECT_EQ(0, m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			m1[i][j] = 1;
	ASSERT_NO_THROW(m2 = m2 + m1);
	EXPECT_EQ(1, m2[0][0]);
	EXPECT_EQ(1, m2[0][1]);
	EXPECT_EQ(1, m2[1][0]);
	EXPECT_EQ(1, m2[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(4), m2(2);
	ASSERT_ANY_THROW(m2 + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 2; j++)
			m1[i][j] = 1;
	m2 = m1;
	ASSERT_NO_THROW(m2 = m2 * m1);
	EXPECT_EQ(2, m2[0][0]);
	EXPECT_EQ(2, m2[0][1]);
	EXPECT_EQ(2, m2[1][0]);
	EXPECT_EQ(2, m2[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(4), m2(2);
	ASSERT_ANY_THROW(m2 * m1);
}

