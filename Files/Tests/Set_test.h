#ifndef SET_TEST_H
#define SET_TEST_H

#include <iostream>
#include "../Header Files/Set.h"
#include "../Header Files/Char.h"
#include "../Header Files/Int.h"
#include "../Header Files/Logical.h"
#include "../Header Files/String.h"

/* The deep_copy() method has been well-tested and hence applied to help check memory leaks. */

namespace Set_test
{
	using std::cout;
	using std::endl;
	
	void build_AB(Set * & A, Set * & B)
	{
		cout << "\n----------- Constructing frequently used Sets A and B. -------------\n\n";
		Tuple *t = new Tuple(new vector<Elem *>{new String("INTJ")});
		vector<Elem *> *elems = new vector<Elem *>{ new String("Hello"), new Logical(true), t, new Int(27), new Char('J')};
		A = new Set(elems, DIRECT_ASSIGN);
		cout << "A = " << A->to_string() << endl;

		Tuple *t2 = new Tuple(new vector<Elem *>{ new String("Suits")});
		vector<Elem *> *elems2 = new vector<Elem *>{ new String("World"), new Logical(false), t2, new Int(06), new Char('J'), new Int(1996)};
		B = new Set(elems2, DIRECT_ASSIGN);
		cout << "B = " << B->to_string() << endl << endl;
	}

	void cardinality(Set * & A, Set * & B)
	{
		cout << "\n----------- Testing the cardinality() method for Sets. -------------\n\n";
		cout << "|A| = " << A->cardinality() << endl;
		cout << "|B| = " << B->cardinality() << endl << endl;
	}

	void _union(Set * & A, Set * & B)
	{
		cout << "\n------------- Testing the _union() method for Sets. ----------------\n\n";
		Set * A_ = (Set *) A->deep_copy();
		Set * B_ = (Set *) B->deep_copy();

		Set * AuB = A_->_union(*B_);
		cout << "A U B = " << AuB->to_string() << endl << endl;
		delete A_, B_, AuB;
	}

	void intersection(Set * & A, Set * & B)
	{
		Set * A_ = (Set *)A->deep_copy();
		Set * B_ = (Set *)B->deep_copy();

		Set * AandB = A_->intersection(*B_);
		cout << "\n---------- Testing the intersection() method for Sets. -------------\n\n";
		cout << "A & B = " << AandB->to_string() << endl << endl;
		delete A_, B_, AandB;
	}
	
	void cartesian_product(Set * & A, Set * & B)
	{
		Set * A_ = (Set *)A->deep_copy();
		Set * B_ = (Set *)B->deep_copy();

		Set * AxB = A_->cartesian_product(*B_);
		cout << "\n------- Testing the cartesian_product() method for Sets. -----------\n\n";
		cout << "A x B = " << AxB->to_string() << endl << endl;
		delete A_, B_, AxB;
	}

	void exclusion(Set * & A, Set * & B)
	{
		Set * A_ = (Set *)A->deep_copy();
		Set * B_ = (Set *)B->deep_copy();

		Set * AwoB = A->exclusion(*B);
		cout << "\n------------- Testing the exclusion() method for Sets. -------------\n\n";
		cout << "A \\ B = " << AwoB->to_string() << endl << endl;
		delete A_, B_, AwoB;
	}

	void access(Set * & A, Set * & B)
	{
		cout << "\n-------------- Testing the [] operator method for Sets. ------------\n\n";
		cout << "A[0] = " << (*A)[0]->to_string() << endl << endl;
		cout << "B[0] = " << (*B)[0]->to_string() << endl << endl << endl;
	}

	void homoset()
	{
		cout << "\n--------------- Testing the homoset() method for Sets. -------------\n\n";
		Set C(new vector<Elem *>{ new Int(27), new Int( 6 ), new Int(1996) });
		Set D(new vector<Elem *>{ new Int(27), new Char('6'), new Int(1996) });

		cout << C.to_string();
		if (C.homoset()) 
			cout << " is a homoset with homotype " << C.homotype() << endl; 
		else 
			cout << " is not a homoset" << endl;

		cout << D.to_string();
		if (D.homoset())
			cout << " is a homoset with homotype " << D.homotype() << endl;
		else
			cout << " is not a homoset" << endl << endl;
	}

	void subset(Set * & A, Set * & B)
	{
		
		cout << "A[0, 2] = " << A->subset(0, 2)->to_string() << endl;
		cout << "B[1, 4] = " << B->subset(1, 4)->to_string() << endl << endl;
	}
	
	void subset_of()
	{
		cout << "\n------------- Testing the subset_of() method for Sets. -----------\n\n";
		Set E(new vector<Elem *>{ new Int(1), new Int(2), new Char('3'), new Logical(true) });
		Set F(new vector<Elem *>{ new Int(1), new Char('3') });

		Set G(new vector<Elem *>{ new Tuple(new vector<Elem *>{ new Int(1), new Logical(false) }), new Char(('X')) });
		Set H(new vector<Elem *>{ new Tuple(new vector<Elem *>{ new Int(1), new Logical(false) })});

		cout << F.to_string() << " c " << E.to_string() << " = " << F.subset_of(E) << endl;
		cout << G.to_string() << " c " << H.to_string() << " = " << G.subset_of(H) << endl << endl;
	}

	void equality()
	{
		cout << "\n---------------- Testing the == operator for Sets. --------------\n\n";
		Set I(new vector<Elem *> {
			new Int(1), 
			new Tuple(new vector<Elem *>{ new String("Yo") }),
			new Logical(true),
			new String("INTJ"),
			new Char('T')
		});
		Set J(new vector<Elem *> { 
			new Int(1), 
			new Tuple(new vector<Elem *>{ new String("Yo") }),
			new Logical(true),
			new String("INTJ"),
			new Char('T')
		});
		Set K(new vector<Elem *>{
			new Int(1), 
			new Tuple(new vector<Elem *>{ new String("Yp") }),
			new Logical(true),
			new String("INTJ"),
			new Char('T')
		});
		cout << I.to_string() << " == " << J.to_string() << " = " << (I == J) << endl;
		cout << I.to_string() << " == " << K.to_string() << " = " << (I == K) << endl << endl;
	}
	
	void test_all()
	{
		Set * A = nullptr, * B = nullptr;
		build_AB(A, B);	cardinality(A, B);
		_union(A, B);	intersection(A, B);
		access(A, B);	homoset();
		subset(A, B);	subset_of();
		equality();
		cartesian_product(A, B);
		exclusion(A, B);
	}
}

#endif