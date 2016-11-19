#define BOOST_TEST_MODULE test_matrix

#include <boost/test/included/unit_test.hpp>
#include "matrix.hpp"

BOOST_AUTO_TEST_SUITE(test_matrix)

BOOST_AUTO_TEST_CASE(test_matrix_constructor_1) {
    Matrix<int> matrix({
        {1, 2, 3},
        {4, 5, 6}
    });
    std::cout << matrix << std::endl;
}
    
BOOST_AUTO_TEST_CASE(test_matrix_constructor_2) {
    std::vector<std::vector<int>> vvt = {
        {1, 2, 3},
        {4, 5, 6}
    };
    Matrix<int> matrix(vvt);
    std::cout << matrix << std::endl;
}

BOOST_AUTO_TEST_CASE(test_matrix_add_1) {
    Matrix<int> matrix1({
        {1, 2, 3},
        {4, 5, 6}
    });

    Matrix<int> matrix2({
        {1, 2, 3},
        {4, 5, 6}
    });
    
    std::cout << matrix1.add(matrix2) << std::endl;
}
    
BOOST_AUTO_TEST_CASE(test_matrix_sub_1) {
    Matrix<int> matrix1({
        {1, 2, 3},
        {4, 5, 6}
    });
    
    Matrix<int> matrix2({
        {1, 2, 3},
        {4, 5, 6}
    });
    
    std::cout << matrix1.sub(matrix2) << std::endl;
}
    
BOOST_AUTO_TEST_CASE(test_matrix_mul_1) {
    Matrix<int> matrix1({
        {1, 2, 3},
        {4, 5, 6}
    });
    
    Matrix<int> matrix2({
        {1, 2},
        {3, 4},
        {5, 6}
    });
    
    std::cout << matrix1.mul(matrix2) << std::endl;
}
    
BOOST_AUTO_TEST_CASE(test_matrix_mul_2) {
    Matrix<int> matrix1({
        {1, 2, 3},
        {4, 5, 6}
    });
    
    std::cout << matrix1.mul(2) << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()

