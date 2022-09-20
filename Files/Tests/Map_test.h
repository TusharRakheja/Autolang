#ifndef MAP_TEST_H
#define MAP_TEST_H

#include "Set_test.h"
#include "../Header Files/Map.h"

namespace Map_test
{
	using std::cout;
	using std::endl;

	void build_F(Map *&F)
	{
		cout << "\n\n----------------Testing the Map constructor--------------\n" << endl;
		Set *domain = new Set( new vector<Elem *> {
			new String("Hello"), new String("INTJ"), 
			new Tuple(new vector<Elem *>{ new Int(1), new Int(2) }),
			new  Set (new vector<Elem *>{ new Char('J'), new Char('U')})
		});

		Set *codomain = new Set(new vector < Elem * > {
			new String("World!"), new Logical(true),
			new Tuple(new vector<Elem *>{ new Int(3), new Int(4) }),
			new  Set (new vector<Elem *>{ new Char('N'), new Char('E')}),
			new Int(1996)
		});

		F = new Map(domain, codomain);
	}

	void test_add_mapping(Map *&F)
	{
		cout << "\n\n-------------Testing the add_mapping() method------------\n" << endl;
		for (int i{ 0 }; i < F->domain_s->cardinality(); i++)
			F->add_maping(*(*F->domain_s)[i], *(*F->codomain_s)[i]);
	} 

	void test_to_string(Map *&F)
	{
		cout << "\n\n--------------Testing the to_string() method-------------\n" << endl;
		cout << "F = " << F->to_string() << endl;
	}

	void test_sets(Map *&F)
	{
		cout << "\n\n--Testing the domain(), codomain(), and range() methods--\n" << endl;
		cout << "  domain(F) = " << F->domain()->to_string() << endl;
		cout << "codomain(F) = " << F->codomain()->to_string() << endl;
		cout << "   range(F) = " << F->range()->to_string() << endl;
	}

	void test_access_op(Map *&F)
	{
		cout << "\n\n---------------Testing the [] operator-------------------\n" << endl;
		String s("Hello");

		cout << "F[" << s.to_string() << "] = " << (*F)[s]->to_string() << endl;

		Elem *e = (*F->domain_s)[2];	

		cout << "F[" << e->to_string() << "] = " << (*F)[*e]->to_string() << endl;
	}

	void test_composed_with(Map *&F)
	{
		cout << "\n\n-----------Testing the composition operator-------------\n" << endl;

		Set *domain_1 = new Set(new vector < Elem * >{
			new String("World!"),
			new Tuple(new vector<Elem *>{ new Int(3), new Int(4) }),
			new  Set(new vector<Elem *>{ new Char('N'), new Char('E') }),
			new Int(1996)
		});

		Set *domain_2 = new Set(new vector < Elem * >{
			new String("World!"), new Logical(true),
			new Tuple(new vector<Elem *>{ new Int(3), new Int(4) }),
			new  Set(new vector<Elem *>{ new Char('N'), new Char('E') }),
		});
		
		Set *codomain = new Set(new vector < Elem * > {
			new String("Greenback Boogey!"), new Int(4)
		});

		Map *composition_candidate_1 = new Map(domain_1, codomain);
		Map *composition_candidate_2 = new Map(domain_2, codomain);
		

		String *s1 = (String *)(*domain_1)[0]; String *s2 = (String *)(*codomain)[0];
		Tuple *t = (Tuple *)(*domain_1)[1]; Int *i = (Int *)(*codomain)[1];

		composition_candidate_1->add_maping(*s1, *s2);
		composition_candidate_2->add_maping(*s1, *s2);
		composition_candidate_1->add_maping(*t, *i);
		composition_candidate_2->add_maping(*t, *i);

		Map *gof_1 = composition_candidate_1->composed_with(*F);
		Map *gof_2 = composition_candidate_2->composed_with(*F);

		cout << "\nComposing with a map with domain: " << endl;
		cout << "\n1. " << domain_1->to_string() << " with F";

		if (gof_1 != nullptr)
			cout << " is possible, and the resulting map is :\n" <<gof_1->to_string() << endl << endl;
		else
			cout << " is not possible, since the range of F is !c of its domain." << endl << endl;

		cout << "\n2. " << domain_2->to_string() << " with F";

		if (gof_2 != nullptr)
			cout << " is possible, and the resulting map is :\n" << gof_2->to_string() << endl << endl;
		else
			cout << " is not possible, since the range of F is !c of its domain." << endl << endl;

		delete domain_1, domain_2, codomain, composition_candidate_1, composition_candidate_2, gof_1, gof_2;
	}

	void test_deep_copy(Map *&F)
	{
		cout << "\n\n------------Testing the deep_copy() method--------------\n" << endl;
		
		cout << "\nLet F' := F. " << endl << endl;

		Map *F_prime = (Map *) F->deep_copy();

		cout << "F' = " << F_prime->to_string() << endl;
		cout << "F  = " << F->to_string() << endl;
		cout << "(F' == F) = " << (*F_prime == *F) << endl << endl;

		cout << "We're now adding an extra element to the codomain of F'." << endl;

		F_prime->domain_s->elems->push_back(new String("Troublemaker"));
		cout << "(F' == F) = " << (*F_prime == *F) << endl << endl; 
		delete F_prime;
	}

	void test_all()
	{
		Map *F = nullptr;
		build_F(F);
		test_add_mapping(F);
		test_to_string(F);
		test_sets(F);
		test_access_op(F);
		test_composed_with(F);
		test_deep_copy(F);
		delete F;
	}
}

#endif