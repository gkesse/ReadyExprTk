//===============================================
#ifndef _GExprTkLib_
#define _GExprTkLib_
//===============================================
#include <iostream>
#include <string>
//===============================================
#include <exprtk.hpp>
//===============================================
using namespace std;
//===============================================
#ifdef DLL_APP
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
//===============================================
class GExprTkLib {
public:
	GExprTkLib();
	~GExprTkLib();
	void setExpr(string expr);
	void addVariable(string key, double& value);
	void addVariable(string key, string& value);
	void addConstant(string key, double value);
	void addVector(string key, vector<double>& value);
	void addFunction(string funcName, exprtk::ifunction<double>& funcPtr);
	void addFunction(string funcName, exprtk::symbol_table<double>::ff01_functor funcPtr);
	void addFunction(string funcName, exprtk::symbol_table<double>::ff02_functor funcPtr);
	void addFunction(string funcName, exprtk::symbol_table<double>::ff03_functor funcPtr);
	void addFunction(string funcName, string funcText, string v1);
	void addFunction(string funcName, string funcText, string v1, string v2);
	void addFunction(string funcName, string funcText, string v1, string v2, string v3);
	void createVariable(string varName);
	void setVariable(string varName, double varValue);
	double getVariable(string varName);
	void setConstants();
	void setSymbols();
	void getSymbols();
	void compile();
	double eval();

private:
	exprtk::expression<double> m_exprRun;
	exprtk::symbol_table<double> m_symbol;
	exprtk::parser<double> m_parser;
	exprtk::function_compositor<double> m_compositor;
	string m_exprText;
};
//===============================================
#endif
//===============================================
