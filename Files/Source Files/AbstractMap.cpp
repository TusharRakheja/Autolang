#include "../Header Files/AbstractMap.h"
#include "../Header Files/ExpressionTree.h"
#include "../Header Files/ProgramVars.h"

/* Implementations for methods in AbstractMap. */

AbstractMap::AbstractMap(string &mapping_scheme_full) : Elem(ABSTRACT_MAP)
{
	this->domain = nullptr;
	this->codomain = nullptr;
	int start = mapping_scheme_full.find("->") + 2;
	while (isspace(mapping_scheme_full[start])) start++;
	this->mapping_scheme = mapping_scheme_full.substr(start, mapping_scheme_full.size() - start);
}

void AbstractMap::add_scheme(string &mapping_scheme_full)
{
	int start = mapping_scheme_full.find("->") + 2;
	while (isspace(mapping_scheme_full[start])) start++;
	this->mapping_scheme = mapping_scheme_full.substr(start, mapping_scheme_full.size() - start);	
}

AbstractMap::AbstractMap(shared_ptr<AbstractSet> domain, shared_ptr<AbstractSet> codomain) : Elem(ABSTRACT_MAP)
{
	this->domain = domain;
	this->codomain = codomain;
}

AbstractMap::AbstractMap(shared_ptr<AbstractSet> domain, shared_ptr<AbstractSet> codomain, string &mapping_scheme_full) : Elem(ABSTRACT_MAP)
{	
	this->domain = domain; 
	this->codomain = codomain;
	int start = mapping_scheme_full.find("->") + 2;
	while (isspace(mapping_scheme_full[start])) start++;
	this->mapping_scheme = mapping_scheme.substr(start, mapping_scheme.size() - start);
}

shared_ptr<AbstractMap> AbstractMap::composed_with(shared_ptr<AbstractMap> g)	// Returns an abstract_map (this composed with g).
{
	// For the comments that follow, this == f. Just for convenience, really.
	
	// under f : elem -> f[elem], where f[elem] represents some transformation.
	// under g : elem -> g[elem], where g[elem] represents some other transformation.
	// We need to return f o g. under f o g : elem -> f[g[elem]]

	string scheme_fog = this->mapping_scheme;

	// In the mapping scheme of f, wherever we see an (x), we'll replace that with (g[(x)]).

	vector<string> scheme_parts;
	int pos = scheme_fog.find("(x)");
	while (pos != string::npos)
	{
		scheme_parts.push_back(scheme_fog.substr(0, pos));
		scheme_parts.push_back("(" + g->mapping_scheme + ")");
		scheme_fog = scheme_fog.substr(pos + 3, scheme_fog.size() - (pos + 3));
		pos = scheme_fog.find("(x)");
	}
	scheme_parts.push_back(scheme_fog);
	scheme_fog = "";
	for (auto &part : scheme_parts) scheme_fog += part;
	
	shared_ptr<AbstractMap> fog = shared_ptr<AbstractMap>{new AbstractMap()};
	fog->domain = g->domain;
	fog->codomain = this->codomain;
	fog->mapping_scheme = scheme_fog;
	return fog;
}

shared_ptr<Elem> AbstractMap::operator[](Elem & pre_image)
{
	if (domain != nullptr && !domain->has(pre_image)) program_vars::raise_error("Mapping unsuccessful. Pre-image not found in domain.");
	string to_be_evaluated = this->mapping_scheme;		// We'll replace all instances of 'elem' with elem->to_string().
	while (to_be_evaluated.find("(x)") != string::npos)	// Iteratively replace the instances in to_be_evaluated.
	{
		int elem_pos = to_be_evaluated.find("(x)");
		string part1 = to_be_evaluated.substr(0, elem_pos);
		string part2 = "(" + pre_image.to_string_raw() + ")";
		string part3 = to_be_evaluated.substr(elem_pos + 3, to_be_evaluated.size() - (elem_pos + 3));
		to_be_evaluated = part1 + part2 + part3;
	}
	ExpressionTree eval(to_be_evaluated);
	shared_ptr<Elem> image = eval.evaluate();
	if (codomain != nullptr && !codomain->has(*image)) program_vars::raise_error("Mapping unsuccessful. Pre-image not found in domain."); 
	return image;
}

const shared_ptr<Elem> AbstractMap::operator[](Elem & pre_image) const
{
	if (domain != nullptr && !domain->has(pre_image)) program_vars::raise_error("Mapping unsuccessful. Pre-image not found in domain.");
	string to_be_evaluated = this->mapping_scheme;		// We'll replace all instances of 'elem' with elem->to_string().
	while (to_be_evaluated.find("(x)") != string::npos)	// Iteratively replace the instances in to_be_evaluated.
	{
		int elem_pos = to_be_evaluated.find("(x)");
		string part1 = to_be_evaluated.substr(0, elem_pos);
		string part2 = "(" + pre_image.to_string_raw() + ")";
		string part3 = to_be_evaluated.substr(elem_pos + 3, to_be_evaluated.size() - (elem_pos + 3));
		to_be_evaluated = part1 + part2 + part3;
	}
	ExpressionTree eval(to_be_evaluated);
	shared_ptr<Elem> image = eval.evaluate();
	if (codomain != nullptr && !codomain->has(*image)) program_vars::raise_error("Mapping unsuccessful. Pre-image not found in domain.");
	return image;
}
