#include "Sale.h"

using namespace sict;

std::ostream& operator<<(std::ostream& os, const iProduct& p)
{
	p.display(os);
	return os;
}

Product::Product(int number, double price)
{
	productNumber = number;
	productPrice = price;
}

double Product::price() const
{
	return productPrice;
}

void Product::display(std::ostream& os) const
{
	os << std::setw(FW) << std::fixed << std::setprecision(2) << productNumber << std::setw(FW) << productPrice << std::endl;
}

iProduct* Product::readRecord(std::ifstream& file)
{
	int number;
	double price;

	file >> number;
	file >> price;

	return new Product(number, price);
}

std::unordered_map<std::string, double> TaxableProduct::taxes
{
	{ "H", 0.13},
	{ "P", 0.08}
};

TaxableProduct::TaxableProduct(int number, double price, std::string tax)
	: Product(number, price), productTax(tax)
{

}

double TaxableProduct::price() const
{
	auto found = taxes.find(productTax);

	if (found == taxes.end())
	{
		return productPrice;
	}
	else
	{
		return productPrice + found->second;
	}
}

void TaxableProduct::display(std::ostream& os) const
{
	os << std::setw(FW) << std::fixed << std::setprecision(2) << productNumber << std::setw(FW) << productPrice << ' ' <<
		productTax + "ST" << std::endl;
}

iProduct* TaxableProduct::readRecord(std::ifstream& file)
{
	std::string str;
	std::istringstream istr;

	std::getline(file, str);
	istr.str(str);

	int number;
	double price;
	std::string tax;

	istr >> number;
	istr >> price;
	istr >> tax;
	if (tax == "")
	{
		return new Product(number, price);
	}
	else
	{
		return new TaxableProduct(number, price, tax);
	}
}

Sale::Sale(const char* fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		throw "Can't open file";
	}
	else
	{
		TaxableProduct temp(0, 0.0, "");

		while (!file.eof())
		{
			products.push_back(temp.readRecord(file));
		}
	}

	file.close();
}

void Sale::display(std::ostream& os) const
{
	os << std::setw(FW) << "Product No" << '\t' << "Cost Taxable" << std::endl;
	for (auto& p : products)
	{
		p->display(os);
	}
}
