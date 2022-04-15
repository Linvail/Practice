#include "Cpp14Features.h"

#include <utility>      // std::forward / std::move
#include <iostream>
#include <vector>
#include <chrono>

namespace Cpp14Features
{
	// function with lvalue and rvalue reference overloads:
	void overloaded( const int& x ) { std::cout << "[lvalue]"; }
	void overloaded( int&& x ) { std::cout << "[rvalue]"; }

	// function template taking rvalue reference to deduced type:
	template <class T> void fn
		(
		T&& x //!< && operator signifies either an rvalue reference, or a universal reference (either rvalue or lvalue) depending on the context.
		)
	{
		overloaded( x );                     // Always an lvalue. All named values( such as function parameters ) always evaluate as lvalues( even those declared as rvalue references )
		overloaded( std::forward<T>( x ) );  // rvalue if argument is rvalue
	}

	//----------------------------------------------------------
	// std::forward
	// If arg is an lvalue reference, the function returns arg without modifying its type.
	// This is a helper function to allow perfect forwarding of arguments taken as rvalue references to deduced types, preserving any potential move semantics involved.
	//
	// The need for this function stems from the fact that all named values( such as function parameters ) always evaluate as lvalues( even those declared as rvalue references ),
	// and this poses difficulties in preserving potential move semantics on template functions that forward arguments to other functions.
	//----------------------------------------------------------
	void test_forward()
	{
		std::cout << "* Test universal reference and std::forward.\n";

		int a;

		std::cout << "calling fn with lvalue: ";
		fn( a );
		std::cout << '\n';

		std::cout << "calling fn with rvalue: ";
		fn( 0 );
		std::cout << '\n';
	}

	class MovableClass
	{
	public:
		MovableClass( int&& aValue ) : mData( aValue )
		{
			std::cout << "Constructor. mData: " << mData << "\n";
		}

		// Copy constructor.
		MovableClass( const MovableClass& aOther )
			: mData( aOther.mData )
		{
			std::cout << "Copy Constructor. mData: " << mData << "\n";
		}

		// Move constructor.
		MovableClass(MovableClass&& aOther) noexcept
			: mData( std::move( aOther.mData ) )
		{
			aOther.mData = -1;
			std::cout << "Move Constructor. mData: " << mData << "\n";
		}

		// Copy assignment operator.
		MovableClass& operator=( const MovableClass& aOther )
		{
			this->mData = aOther.mData;
			std::cout << "Copy assignment. mData: " << mData << "\n";
			return *this;
		}

		// Move assignment operator.
		MovableClass& operator=( MovableClass&& aOther ) noexcept
		{
			this->mData = aOther.mData;
			aOther.mData = -1;
			std::cout << "Move assignment. mData: " << mData << "\n";
			return *this;
		}

		// Destructor
		~MovableClass()
		{
			std::cout << "Destructor. mData: " << mData << "\n";
		}

		int mData;
	};

	MovableClass createMyCustom()
	{
		std::cout << "Start createMyCustom.\n";
		MovableClass obj( 1 );

		std::cout << "End createMyCustom.\n";

		return obj;
	}

	void test_move()
	{

		{
			std::cout << "* Test compiler's Return value optimization (copy elision).\n";

			// The test result shows that VC complier applies "Return value optimization (copy elision)" even in Debug mode.
			// The MyCustom object is only created once. Move constructor is called once and Copy constructor is never called.
			MovableClass obj( createMyCustom() );

			// If we use move semantic, it produces more unnecessay constructors/destructors. The performace becomes wrose.
			//MovableClass obj( std::move( createMyCustom() ) );

			std::cout << "End of Block.\n";
		}

		std::cout << std::endl;

		// Move constructor is called once.
		{
			std::cout << "* Test push_back a temporary object.\n";

			std::vector<MovableClass> v;
			std::cout << "Push back a MovableClass.\n";
			v.push_back( MovableClass( 2 ) );

			std::cout << "End of Block.\n\n";
		}

		std::cout << std::endl;

		// Move constructor is called twice.
		{
			std::cout << "* Test push_back a temporary object returned by a function.\n";

			std::vector<MovableClass> v;
			std::cout << "Push back a MovableClass.\n";
			v.push_back( createMyCustom() );

			std::cout << "End of Block.\n";
		}

		std::cout << std::endl;

		// Copy constructor is called once and Move constructor is called once.
		{
			std::cout << "* Test std::move and move constructor.\n";

			MovableClass obj1( 3 );
			MovableClass obj2( obj1 );
			obj2.mData = 2;

			MovableClass obj3( std::move( obj2 ) );

			std::cout << "End of Block.\n";
		}

		std::cout << std::endl;

		using std::chrono::high_resolution_clock;
		using std::chrono::duration_cast;
		using std::chrono::duration;
		using std::chrono::milliseconds;

		// Test of Concatenating two vectors.
		{
			std::cout << "* Concatenating two vectors without std::make_move_iterator.\n";

			MovableClass tmp( 1 );

			std::cout << "Define 1st vector\n";
			std::vector<MovableClass> v1( 1, tmp ); // Causes one call to copy constructor.
			v1.reserve( 3 ); // This causes one call to move constructor and one call to destructor due to reallocation.

			std::cout << "Define 2nd vector\n";
			std::vector<MovableClass> v2( 2, tmp ); // Causes two calls to copy constructor.

			std::cout << "Concatenate 2 vectors\n";
			v1.insert( v1.end(), v2.begin(), v2.end() ); // Causes two calls to copy constructor.

			std::cout << "End of Block.\n";
		}

		std::cout << std::endl;

		// Test of Concatenating two vectors with std::make_move_iterator
		{
			std::cout << "* Concatenating two vectors with std::make_move_iterator.\n";

			MovableClass tmp( 1 );

			std::cout << "Define 1st vector\n";
			std::vector<MovableClass> v1( 1, tmp ); // Causes one call to copy constructor.
			v1.reserve( 3 ); // This causes one call to move constructor and one call to destructor due to reallocation.

			std::cout << "Define 2nd vector\n";
			std::vector<MovableClass> v2( 2, tmp ); // Causes two calls to copy constructor.

			std::cout << "Concatenate 2 vectors\n";
			v1.insert(
				v1.end(),
				std::make_move_iterator( v2.begin() ),
				std::make_move_iterator( v2.end() ) ); // Causes two calls to move constructor.

			std::cout << "End of Block.\n";
		}

		std::cout << std::endl;
	}



}