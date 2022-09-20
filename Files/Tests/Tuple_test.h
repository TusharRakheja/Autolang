#ifndef TUPLE_TEST_H
#define TUPLE_TEST_H

#include "Set_test.h"

namespace Tuple_test
{
	using std::cout;
	using std::endl;

	void build_AB(Tuple * & A, Tuple * & B)
	{
		cout << "\n----------- Constructing frequently used Tuples A and B. -------------\n\n";
		Set *t = new Set(new vector<Elem *>{ new String("INTJ") });
		vector<Elem *> *elems = new vector<Elem *>{ new String("Hello"), new Logical(true), t, new Int(27), new Char('J') };
		A = new Tuple(elems, DIRECT_ASSIGN);
		cout << "A = " << A->to_string() << endl;

		Set *t2 = new Set(new vector<Elem *>{ new String("Suits") });
		vector<Elem *> *elems2 = new vector<Elem *>{ new String("World"), new Logical(false), t2, new Int(06), new Char('J'), new Int(1996) };
		B = new Tuple(elems2, DIRECT_ASSIGN);
		cout << "B = " << B->to_string() << endl << endl;
	}

	void size(Tuple * & A, Tuple * & B)
	{
		cout << "\n-------------- Testing the size() method for Tuples. ----------------\n\n";
		cout << "|A| = " << A->size() << endl;
		cout << "|B| = " << B->size() << endl << endl;
	}

	void contains(Tuple * & A)
	{
		cout << "\n-------------- Testing the has() method for Tuples. -----------------\n\n";
		String str1("Hello"), str2 ("World");
		Set set1(new vector<Elem *>{ new String("INTJ") });
		Set set2(new vector<Elem *>{ new String("INTP") });

		cout << A->to_string() << " has " << str1.to_string() << " = " << A->has(str1) << endl;
		cout << A->to_string() << " has " << str2.to_string() << " = " << A->has(str2) << endl;
		cout << A->to_string() << " has " << set1.to_string() << " = " << A->has(set1) << endl;
		cout << A->to_string() << " has " << set2.to_string() << " = " << A->has(set2) << endl;
	}

	void equality()
	{
		cout << "\n---------------- Testing the == operator for Sets. --------------\n\n";
		Tuple I(new vector<Elem *>{
			new Int(1),
			new Set(new vector<Elem *>{ new String("Yo") }),
			new Logical(true),
			new String("INTJ"),
			new Char('T')
		});
		Tuple J(new vector<Elem *>{
			new Int(1),
			new Set(new vector<Elem *>{ new String("Yo") }),
			new Logical(true),
			new String("INTJ"),
			new Char('T')
		});
		Tuple K(new vector<Elem *>{
			new Int(1),
			new Set(new vector<Elem *>{ new String("Yp") }),
			new Logical(true),
			new String("INTJ"),
			new Char('T')
		});
		cout << I.to_string() << " == " << J.to_string() << " = " << (I == J) << endl;
		cout << I.to_string() << " == " << K.to_string() << " = " << (I == K) << endl << endl;
	}

	void deep_copy(Tuple * & A)
	{
		cout << "\n------------- Testing the deep_copy() method for Tuples. ------------\n\n";
		cout << "A = " << A->to_string() << endl << endl;

		Tuple *L = (Tuple *)(A->deep_copy());
		cout << "Let L := A. L = " << L->to_string() << ", ";
		cout << "(A == L) = " << (*A == *L) << endl << endl;

		delete (*L)[3];					// Remove the Int 27 from L[3].
		(*L)[3] = new Int(28);				// Put a new Int 28 there.

		cout << "L[3] := 28, L = " << L->to_string() << endl;

		cout << "A = " << A->to_string() << endl << endl;

		cout << "(A == L) = " << (*A == *L) << endl;
		delete L;
	}

	void test_all()
	{
		Tuple * A, * B;
		build_AB(A, B);	
		size(A, B);
		contains(A), equality();
		deep_copy(A);
		delete A;
		delete B;
	}
}

#endif