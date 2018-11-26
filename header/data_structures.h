#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <queue>
#include <array>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::queue;
using std::array;
using std::find_if;
using std::find;
using std::numeric_limits;
using std::min;
using std::to_string;
using std::pair;

using vec2d = vector<vector<int>>;

/********************************* Some types  *************************************/
enum reg_type { IN = 0 , OUT = 1, TEMP = 2 };
enum operation_type { ADD = 0, SUB = 1, MULT = 2, DIV = 3 };
/***********************************************************************************/

/********************************* Edge Register  *************************************/
struct reg
{
	string reg_name;	// the register name
	reg_type type;  	// the register type
	int w; 				// width
	int fw, lr;			// first write, last read

	// constructors
	reg () = default;
	reg (string reg_name, reg_type type, int w, int fw, int lr) 
		: reg_name (reg_name), type (type), w (w), fw (fw), lr (lr) {}

	bool is_compatible (const reg &) const;

private:
	bool in_range (int, int, int) const;
};
/***************************************************************************************/

/********************************* Operation  *************************************/
struct operation
{
	string op_name;
	operation_type type; // operation type
	int w, ts,   		 // width and time step
		i1, i2, out; 	 // the two input registers, and the output register indexes
	vector<int> suc;	 // dependencies
	vector<int> pred;	 // dependencies

	// constructors
	operation () = default;
	operation (string op_name, operation_type type, int w, int ts, int i1, int i2, int out) 
		: op_name (op_name), type (type), w (w), ts (ts), i1 (i1), i2 (i2), out (out) {}

	bool is_compatible (const operation &) const;	
};
/***************************************************************************************/

/********************************* Data Flow Graph *************************************/
class graph
{
public:
	vector<reg> regs;
	vector<operation> ops; 
	array<int, 4> a;

	// constructor
	graph () = default;

	// member methods
	void add_register (string reg_name, int width, reg_type type);
	void add_operation (string op_name, operation_type type, int width, string reg_in1, string reg_in2, string reg_out);	
	bool alap (int l, vector<int> &tl);	
	bool list_r (int l);
	void list_l (int adds, int subs, int mults, int divs);
	void set_lifetime ();
	void print_graph ();
};
/***************************************************************************************/

/********************************* Register Unit *************************************/
struct reg_unit
{
	string reg_name, in_name, out_name, WR_name;
	int w;
	bool is_input;

	reg_unit () = default;
	reg_unit (string reg_name, string in_name, string out_name, string WR_name, int w, bool is_input) 
		: reg_name (reg_name), in_name(in_name), out_name (out_name), WR_name (WR_name), w(w), is_input (is_input) {}
};
/***************************************************************************************/

/********************************* Functional Unit *************************************/
struct fu_unit
{
	string fu_name, i1_name, i2_name, out_name;
	int w;
	operation_type type;

	fu_unit () = default;
	fu_unit (string fu_name, string i1_name, string i2_name, string out_name, int w, operation_type type)
		: fu_name (fu_name), i1_name (i1_name), i2_name (i2_name), out_name (out_name), w (w), type (type) {}
};
/***************************************************************************************/

/*************************************** MUX units *************************************/
struct mux_unit
{
	string mux_name, sel_name;
	int sel_size; 
	int w;
};

struct rmux_unit : public mux_unit
{
	reg_unit *out;
	vector<fu_unit *> in;
};

struct fmux_unit : public mux_unit
{
	fu_unit *out;
	vector<reg_unit *> in;
};
/***************************************************************************************/

/*************************************** Data path *************************************/
class datapath
{
private:
	void create_functional_units (const graph &, const vec2d &);
	void create_register_units (const graph &, const vec2d &);
	void create_register_mux_units (const graph &, const vec2d &, const vec2d &);
	void create_fu_mux_units (const graph &, const vec2d &, const vec2d &);
	void create_output_links (const graph &, const vec2d &);

public:
	vector<fu_unit> funits;
	vector<reg_unit> runits;
	vector<rmux_unit> reg_mux;
	vector<array<fmux_unit, 2>> fu_mux;
	vector<pair<string, string>> outl;

	datapath (const graph &, const vec2d &, const vec2d &);
};
/***************************************************************************************/

#endif