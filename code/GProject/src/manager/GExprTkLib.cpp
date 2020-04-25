//===============================================
#include "GExprTkLib.h"
//===============================================
GExprTkLib::GExprTkLib() {

}
//===============================================
GExprTkLib::~GExprTkLib() {

}
//===============================================
void GExprTkLib::setExpr(string exprText) {
	m_exprText = exprText;
}
//===============================================
void GExprTkLib::addVariable(string key, double& value) {
	m_symbol.add_variable(key, value);
}
//===============================================
void GExprTkLib::addVariable(string key, string& value) {
	m_symbol.add_stringvar(key, value);
}
//===============================================
void GExprTkLib::addConstant(string key, double value) {
	m_symbol.add_constant(key, value);
}
//===============================================
void GExprTkLib::addVector(string key, vector<double>& value) {
	m_symbol.add_vector(key, value);
}
//===============================================
void GExprTkLib::addFunction(string funcName, exprtk::ifunction<double>& funcPtr) {
	m_symbol.add_function(funcName, funcPtr);
}
//===============================================
void GExprTkLib::addFunction(string funcName, exprtk::symbol_table<double>::ff01_functor funcPtr) {
	m_symbol.add_function(funcName, funcPtr);
}
//===============================================
void GExprTkLib::addFunction(string funcName, exprtk::symbol_table<double>::ff02_functor funcPtr) {
	m_symbol.add_function(funcName, funcPtr);
}
//===============================================
void GExprTkLib::addFunction(string funcName, exprtk::symbol_table<double>::ff03_functor funcPtr) {
	m_symbol.add_function(funcName, funcPtr);
}
//===============================================
void GExprTkLib::addFunction(string funcName, string funcText, string v1) {
	m_compositor.add(exprtk::function_compositor<double>::function(funcName, funcText, v1));
}
//===============================================
void GExprTkLib::addFunction(string funcName, string funcText, string v1, string v2) {
	m_compositor.add(exprtk::function_compositor<double>::function(funcName, funcText, v1, v2));
}
//===============================================
void GExprTkLib::addFunction(string funcName, string funcText, string v1, string v2, string v3) {
	m_compositor.add(exprtk::function_compositor<double>::function(funcName, funcText, v1, v2, v3));
}
//===============================================
void GExprTkLib::createVariable(string varName) {
	m_symbol.create_variable(varName);
}
//===============================================
void GExprTkLib::setVariable(string varName, double varValue) {
	m_symbol.get_variable(varName)->ref() = varValue;
}
//===============================================
double GExprTkLib::getVariable(string varName) {
	return m_symbol.get_variable(varName)->value();
}
//===============================================
void GExprTkLib::setConstants() {
	m_symbol.add_constants();
}
//===============================================
void GExprTkLib::setSymbols() {
	m_exprRun.register_symbol_table(m_symbol);
}
//===============================================
void GExprTkLib::getSymbols() {
	m_symbol = m_compositor.symbol_table();
}
//===============================================
void GExprTkLib::compile() {
	m_parser.compile(m_exprText, m_exprRun);
}
//===============================================
double GExprTkLib::eval() {
	return m_exprRun.value();
}
//===============================================
