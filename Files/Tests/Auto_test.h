#ifndef AUTO_TEST_H
#define AUTO_TEST_H

#include "../Header Files/Auto.h"
#include <iostream>

using std::cout;
using std::endl;

// A will be an automaton that accepts all even non-negative integers in their binary representation.
// B will be an automaton that accepts all non-negative integeral multiples of 3 in their binary representation.

namespace Auto_test
{
	void build_AB(Auto * & A, Auto * & B)
	{
		cout << "\n\n-------------------Building Automata A & B-------------------\n" << endl;
		Set * alphabet = new Set(new vector < Elem * >{
			new Char('0'), new Char('1')
		});
		Set * states_A = new Set( new vector < Elem * > {		// States for A.
			new String("20"), new String("21"), new String("\\")	// "Auto for 2, state 0", "Auto for 2, state 1".
		});
		Set * states_B = new Set(new vector < Elem * > {
			new String("30"), new String("31"), new String("32"), new String("\\")
		});
		Map * delta_A = new Map(states_A->cartesian_product(*alphabet), states_A);
		Map * delta_B = new Map(states_B->cartesian_product(*alphabet), states_B);

		/* Pre-images for the mappings for A's transition function. */

		Tuple A_preim1(new vector<Elem*>{ (*states_A)[0]->deep_copy(), (*alphabet)[0]->deep_copy() }, DIRECT_ASSIGN);
		Tuple A_preim2(new vector<Elem*>{ (*states_A)[0]->deep_copy(), (*alphabet)[1]->deep_copy() }, DIRECT_ASSIGN);
		Tuple A_preim3(new vector<Elem*>{ (*states_A)[1]->deep_copy(), (*alphabet)[0]->deep_copy() }, DIRECT_ASSIGN);
		Tuple A_preim4(new vector<Elem*>{ (*states_A)[1]->deep_copy(), (*alphabet)[1]->deep_copy() }, DIRECT_ASSIGN);
		Tuple A_preim5(new vector<Elem*>{ (*states_A)[2]->deep_copy(), (*alphabet)[0]->deep_copy() }, DIRECT_ASSIGN);
		Tuple A_preim6(new vector<Elem*>{ (*states_A)[2]->deep_copy(), (*alphabet)[1]->deep_copy() }, DIRECT_ASSIGN);

		String A_im135(*(String *)(*states_A)[0]);
		String A_im246(*(String *)(*states_A)[1]);

		delta_A->add_maping(A_preim1, A_im135);		// delta_A("20", '0') = "20" 
		delta_A->add_maping(A_preim2, A_im246);		// delta_A("20", '1') = "21" 
		delta_A->add_maping(A_preim3, A_im135);		// delta_A("21", '0') = "20"
		delta_A->add_maping(A_preim4, A_im246);		// delta_A("21", '1') = "21"
		delta_A->add_maping(A_preim5, A_im135);		// delta_A("\",  '0') = "20"
		delta_A->add_maping(A_preim6, A_im246);		// delta_A("\",  '1') = "21"

		Tuple B_preim1(new vector<Elem*>{ (*states_B)[0]->deep_copy(), (*alphabet)[0]->deep_copy() }, DIRECT_ASSIGN);
		Tuple B_preim2(new vector<Elem*>{ (*states_B)[0]->deep_copy(), (*alphabet)[1]->deep_copy() }, DIRECT_ASSIGN);
		Tuple B_preim3(new vector<Elem*>{ (*states_B)[1]->deep_copy(), (*alphabet)[0]->deep_copy() }, DIRECT_ASSIGN);
		Tuple B_preim4(new vector<Elem*>{ (*states_B)[1]->deep_copy(), (*alphabet)[1]->deep_copy() }, DIRECT_ASSIGN);
		Tuple B_preim5(new vector<Elem*>{ (*states_B)[2]->deep_copy(), (*alphabet)[0]->deep_copy() }, DIRECT_ASSIGN);
		Tuple B_preim6(new vector<Elem*>{ (*states_B)[2]->deep_copy(), (*alphabet)[1]->deep_copy() }, DIRECT_ASSIGN);
		Tuple B_preim7(new vector<Elem*>{ (*states_B)[3]->deep_copy(), (*alphabet)[0]->deep_copy() }, DIRECT_ASSIGN);
		Tuple B_preim8(new vector<Elem*>{ (*states_B)[3]->deep_copy(), (*alphabet)[1]->deep_copy() }, DIRECT_ASSIGN);

		String B_im147(*(String *)(*states_B)[0]);
		String B_im258(*(String *)(*states_B)[1]);
		String B_im36 (*(String *)(*states_B)[2]);
		
		delta_B->add_maping(B_preim1, B_im147);		// delta_B("0", '0') = "0"
		delta_B->add_maping(B_preim2, B_im258);		// delta_B("0", '1') = "1" 
		delta_B->add_maping(B_preim3, B_im36 );		// delta_B("1", '0') = "2"
		delta_B->add_maping(B_preim4, B_im147);		// delta_B("1", '1') = "0"
		delta_B->add_maping(B_preim5, B_im258);		// delta_B("2", '0') = "1"
		delta_B->add_maping(B_preim6, B_im36);		// delta_B("2", '1') = "2"
		delta_B->add_maping(B_preim7, B_im147);		// delta_B("\", '0') = "0"
		delta_B->add_maping(B_preim8, B_im258);		// delta_B("\", '1') = "1"

		Set * start_A = (Set *)(*states_A)[2];
		Set * start_B = (Set *)(*states_B)[3];

		Set * accepting_A = new Set(new vector<Elem *>{ (*states_A)[0] });
		Set * accepting_B = new Set(new vector<Elem *>{ (*states_B)[0] });

		A = new Auto(states_A, alphabet, start_A, delta_A, accepting_A, DIRECT_ASSIGN);
		B = new Auto(states_B, alphabet, start_B, delta_B, accepting_B, DIRECT_ASSIGN);
	}

	void test_AB(Auto * & A, Auto * & B)
	{
		cout << "\n\n-------------------Running queries on A & B------------------\n" << endl;
		String q1("0"), q2(""), q3("100"), q4("011");
		cout << "A accepts \"0\" == " << A->accepts(q1).to_string() << endl;
		cout << "A accepts \"\\\" == " << A->accepts(q2).to_string() << endl;
		cout << "A accepts \"100\" == " << A->accepts(q3).to_string() << endl;
		cout << "A accepts \"011\" == " << A->accepts(q4).to_string() << endl << endl;
		cout << "B accepts \"0\" == " << B->accepts(q1).to_string() << endl;
		cout << "B accepts \"\\\" == " << B->accepts(q2).to_string() << endl;
		cout << "B accepts \"100\" == " << B->accepts(q3).to_string() << endl;
		cout << "B accepts \"011\" == " << B->accepts(q4).to_string() << endl;
	}

	void test_AUB(Auto * & A, Auto * & B)
	{
		cout << "\n\n-------------------Running queries on A U B------------------\n" << endl;
		String q3("100"), q4("011");
		Auto * _A = (Auto *)A->deep_copy();
		Auto * _B = (Auto *)B->deep_copy();
		Auto * AUB = _A->accepts_union(B);
		cout << "A U B accepts \"100\" == " << AUB->accepts(q3).to_string() << endl;	// Should be true.
		cout << "A U B accepts \"011\" == " << AUB->accepts(q4).to_string() << endl;	// Should be true.
		delete _A, _B, AUB;
	}
	
	void test_AandB(Auto * & A, Auto * & B)
	{
		cout << "\n\n-------------------Running queries on A & B------------------\n" << endl;
		String q3("100"), q4("011"), q5("110");
		Auto * _A = (Auto *)A->deep_copy();
		Auto * _B = (Auto *)B->deep_copy();
		Auto * AandB = _A->accepts_intersection(B);
		cout << "A & B accepts \"100\" == " << AandB->accepts(q3).to_string() << endl;	// Should be false. 
		cout << "A & B accepts \"011\" == " << AandB->accepts(q4).to_string() << endl;	// Should be false.
		cout << "A & B accepts \"110\" == " << AandB->accepts(q5).to_string() << endl;  // Should be true.
		delete _A, _B, AandB;
	}

	void test_AsansB(Auto * & A, Auto * & B)
	{
		cout << "\n\n-------------------Running queries on A \\ B------------------\n" << endl;
		String q3("100"), q4("011"), q5("110");
		Auto * _A = (Auto *)A->deep_copy();
		Auto * _B = (Auto *)B->deep_copy();
		Auto * AsansB = _A->accepts_exclusively(B);
		cout << "A \\ B accepts \"100\" == " << AsansB->accepts(q3).to_string() << endl;	// Should be true.
		cout << "A \\ B accepts \"011\" == " << AsansB->accepts(q4).to_string() << endl;	// Should be false.
		cout << "A \\ B accepts \"110\" == " << AsansB->accepts(q5).to_string() << endl;	// Should be false.
		delete _A, _B, AsansB;
	}

	void test_all()
	{
		Auto * A, * B;
		build_AB(A, B);
		test_AB(A, B);
		test_AUB(A, B);
		test_AandB(A, B);
		test_AsansB(A, B);
		cout << endl;
	}
}

#endif