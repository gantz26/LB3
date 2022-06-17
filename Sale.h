#ifndef SALE_H
#define SALE_H

#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

extern int FW;

namespace sict
{
	class iProduct
	{
	protected:
		int productNumber;
		double productPrice;

	public:
		virtual double price() const = 0;
		virtual void display(std::ostream& os) const = 0;
		virtual iProduct* readRecord(std::ifstream& file) = 0;

		friend std::ostream& operator<<(std::ostream& os, const iProduct& p);
	};

	class Product : public iProduct
	{
	public:
		Product(int number = 0, double price = 0.0);

		double price() const override;
		void display(std::ostream& os) const override;
		iProduct* readRecord(std::ifstream& file) override;
	};

	class TaxableProduct : public Product
	{
	private:
		static std::unordered_map<std::string, double> taxes;
		std::string productTax;

	public:
		TaxableProduct(int number = 0, double price = 0.0, std::string tax = "");

		double price() const override;
		void display(std::ostream& os) const override;
		iProduct* readRecord(std::ifstream& file) override;
	};

	class Sale
	{
	private:
		std::vector<iProduct*> products;

	public:
		Sale(const char* fileName);

		void display(std::ostream& os) const;
	};
}

#endif