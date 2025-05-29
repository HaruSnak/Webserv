#!/bin/bash

echo "#ifndef ${1^^}_HPP
# define ${1^^}_HPP

# include <iostream>
# include <string>

class $1
{
    private:

    public:
        $1();
        $1(const $1 &copy);
        ~$1();
        $1& operator=($1& copy);
};

#endif" > includes/$1.hpp

echo "#include \"../includes/$1.hpp\"

//------------------------------- CONSTRUCTOR --------------------------------/

$1::$1()
{
    std::cout << \"Default constructor called\" << std::endl;
}

$1::$1(const $1 &copy)
{
    std::cout << \"Name constructor called\" << std::endl;
}

//------------------------------- DESTRUCTOR --------------------------------/

$1::~$1()
{
    std::cout << \"Destructor called\" << std::endl;
}

//------------------------------- OVERLOAD OPERATOR --------------------------------/

$1& $1::operator=($1& copy)
{
    if (this != &copy)
    {

    }
    return (this);
}

//------------------------------- FUNCTIONS --------------------------------*/


" > srcs/$1.cpp