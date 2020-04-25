//===============================================
#include "GExprTkLib.h"
//===============================================
typedef double T;
//===============================================
static void testDefault(int argc, char** argv);
static void testClampWave(int argc, char** argv);
static void testSquareWave(int argc, char** argv);
static void testMultiplications(int argc, char** argv);
static void testFibonacci(int argc, char** argv);
static void testFunction(int argc, char** argv);
//===============================================
int main(int argc, char** argv) {
	cout << __FUNCTION__ << "()\n";
	bool lRunFlag = 0;
	for(int i = 1; i < argc;) {
		string lKey = argv[i++];
		if(lKey == "clamp") {testClampWave(argc, argv); lRunFlag = 1; break;}
		if(lKey == "square") {testSquareWave(argc, argv); lRunFlag = 1; break;}
		if(lKey == "poly") {testMultiplications(argc, argv); lRunFlag = 1; break;}
		if(lKey == "fibo") {testFibonacci(argc, argv); lRunFlag = 1; break;}
		if(lKey == "func") {testFunction(argc, argv); lRunFlag = 1; break;}
		break;
	}
	if(lRunFlag == 0) {testDefault(argc, argv);}
	return 0;
}
//===============================================
static void testDefault(int argc, char** argv) {
	cout << __FUNCTION__ << "()\n";
	string lExprText = ""
			"(x - 5)^2";

	GExprTkLib lExprTk;
	lExprTk.setExpr(lExprText);

	double x, y;

	lExprTk.addVariable("x", x);
	lExprTk.setSymbols();
	lExprTk.compile();
	for(x = 1; x < 10; x += 1) {
		y = lExprTk.eval(); cout << "x : " << x << " ; y: " << y << "\n";
	}
}
//===============================================
static void testClampWave(int argc, char** argv) {
	cout << __FUNCTION__ << "()\n";
	string lExprText = ""
			"clamp(-1.0,sin(2 * pi * x) + cos(x / 2 * pi),+1.0)";

	GExprTkLib lExprTk;
	lExprTk.setExpr(lExprText);

	T x;

	lExprTk.addVariable("x",x);
	lExprTk.setConstants();
	lExprTk.setSymbols();
	lExprTk.compile();

	int iCount = 0;
	for (x = T(-5); x <= T(+5); x += T(0.001)) {
		T y = lExprTk.eval();
		printf("%19.15f\t%19.15f\n",x,y);
		if(iCount++ == 10) break;
	}
}
//===============================================
static void testSquareWave(int argc, char** argv) {
	cout << __FUNCTION__ << "()\n";
	string lExprText = ""
			"a*(4/pi)*"
			"((1 /1)*sin( 2*pi*f*t)+(1 /3)*sin( 6*pi*f*t)+"
			" (1 /5)*sin(10*pi*f*t)+(1 /7)*sin(14*pi*f*t)+"
			" (1 /9)*sin(18*pi*f*t)+(1/11)*sin(22*pi*f*t)+"
			" (1/13)*sin(26*pi*f*t)+(1/15)*sin(30*pi*f*t)+"
			" (1/17)*sin(34*pi*f*t)+(1/19)*sin(38*pi*f*t)+"
			" (1/21)*sin(42*pi*f*t)+(1/23)*sin(46*pi*f*t)+"
			" (1/25)*sin(50*pi*f*t)+(1/27)*sin(54*pi*f*t))";

	GExprTkLib lExprTk;
	lExprTk.setExpr(lExprText);

	static const T pi = T(3.141592653589793238462643383279502);

	const T f = pi / T(10);
	const T a = T(10);
	T t = T(0);

	lExprTk.addVariable("t",t);
	lExprTk.addConstant("f",f);
	lExprTk.addConstant("a",a);

	lExprTk.setConstants();
	lExprTk.setSymbols();
	lExprTk.compile();

	const T delta = T(4) * pi / T(1000);

	int iCount = 0;
	for (t = T(-2) * pi; t <= T(+2) * pi; t += delta) {
		T result = lExprTk.eval();
		printf("%19.15f\t%19.15f\n",t,result);
		if(iCount++ == 10) break;
	}
}
//===============================================
static void testMultiplications(int argc, char** argv) {
	cout << __FUNCTION__ << "()\n";
	string lExprText = ""
			"25x^5 - 35x^4 - 15x^3 + 40x^2 - 15x + 1";

	GExprTkLib lExprTk;
	lExprTk.setExpr(lExprText);

	T r0 = T(0);
	T r1 = T(1);
	T x = T(0);

	lExprTk.addVariable("x",x);
	lExprTk.setSymbols();
	lExprTk.compile();

	const T delta = T(1 / 100.0);

	int iCount = 0;
	for (x = r0; x <= r1; x += delta) {
		T y = lExprTk.eval();
		printf("%19.15f\t%19.15f\n",x,y);
		if(iCount++ == 10) break;
	}
}
//===============================================
static void testFibonacci(int argc, char** argv) {
	cout << __FUNCTION__ << "()\n";
	string lExprText = ""
			"fibonacci(x)";

	GExprTkLib lExprTk;
	lExprTk.setExpr(lExprText);

	lExprTk.addFunction(
			"fibonacci",
			" var w := 0;              "
			" var y := 0;              "
			" var z := 1;              "
			" switch                   "
			" {                        "
			"   case x == 0 : 0;       "
			"   case x == 1 : 1;       "
			"   default     :          "
			"     while ((x -= 1) > 0) "
			"     {                    "
			"       w := z;            "
			"       z := z + y;        "
			"       y := w;            "
			"       z                  "
			"     };                   "
			" }                        ",
			"x");

	T x = T(0);

	lExprTk.getSymbols();
	lExprTk.addVariable("x",x);
	lExprTk.setConstants();
	lExprTk.setSymbols();
	lExprTk.compile();

	int iCount = 0;
	for (size_t i = 0; i < 40; ++i) {
		x = i;
		T y = lExprTk.eval();
		printf("fibonacci(%3d) = %10.0f\n",i,y);
		if(iCount++ == 10) break;
	}
}
//===============================================
struct myfunc : public exprtk::ifunction<T> {
	myfunc(): exprtk::ifunction<T>(2) {
		exprtk::disable_has_side_effects(*this);
	}

	inline T operator()(const T& v1, const T& v2) {
		return T(1) + (v1 * v2) / T(3);
	}
};
//===============================================
inline T myotherfunc(T v0, T v1, T v2) {
	return abs(v0 - v1) * v2;
}
//===============================================
static void testFunction(int argc, char** argv) {
	cout << __FUNCTION__ << "()\n";
	string lExprText = ""
			"myfunc(sin(x / pi), otherfunc(3 * y, x / 2, x * y))";

	GExprTkLib lExprTk;
	lExprTk.setExpr(lExprText);

	T x = T(1);
	T y = T(2);

	myfunc mf;

	lExprTk.addVariable("x",x);
	lExprTk.addVariable("y",y);
	lExprTk.addFunction("myfunc",mf);
	lExprTk.addFunction("otherfunc",myotherfunc);

	lExprTk.setConstants();
	lExprTk.setSymbols();
	lExprTk.compile();

	T result = lExprTk.eval();
	printf("Result: %10.5f\n",result);
}
//===============================================
