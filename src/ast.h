#ifndef __ASTFILE
#define __ASTFILE

#include "dynamic_array.h"
#include "tokenizer.h"

#include "string_util.h"

struct Type;
typedef struct Type Type;

Dynamic_Array_Def(Type*, Array_Type, array_type_)

Dynamic_Array_Def(Array_Type, Array_Array_Type, array_array_type_)

struct Expression_Node;
typedef struct Expression_Node Expression_Node;

typedef struct {
    Expression_Node* expression;
    bool result;
} Directive_If_Node;

typedef enum {
    Directive_If,
} Directive_Kind;

typedef struct {
    Directive_Kind kind;
    union {
        Directive_If_Node if_;
    } data;
} Directive_Node;

Dynamic_Array_Def(Directive_Node, Array_Directive, array_directive_)

struct Item_Node;
typedef struct Item_Node Item_Node;

typedef struct {
    enum {
        Identifier_Single,
        Identifier_Multi,
    } kind;
    union {
        char* single;
        Array_String multi;
    } data;
} Identifier;

typedef enum {
    Type_USize,
    Type_U64,
    Type_U32,
    Type_U16,
    Type_U8,
    Type_F8,
    Type_Ptr,
    Type_Bool,
} Internal_Type;

typedef struct {
    Identifier identifier;
    Item_Node* resolved_node;
} Basic_Type;

typedef struct {
    Type* child;
} Pointer_Type;

typedef struct {
    Array_Type arguments;
    Array_Type returns;
} Procedure_Type;

typedef struct {
    Type* size_type;
    bool has_size;
    Type* element_type;
} BArray_Type;

struct Declaration;
typedef struct Declaration Declaration;

Dynamic_Array_Def(Declaration*, Array_Declaration_Pointer, array_declaration_pointer_)

struct Macro_Syntax_Data;
typedef struct Macro_Syntax_Data Macro_Syntax_Data;

Dynamic_Array_Def(Macro_Syntax_Data*, Array_Macro_Syntax_Data, array_macro_syntax_data_)

struct Macro_Syntax_Kind;
typedef struct Macro_Syntax_Kind Macro_Syntax_Kind;

struct Macro_Syntax_Kind {
    enum {
        Macro_None,
        Macro_Expression,
        Macro_Type,
        Macro_Multiple,
        Macro_Multiple_Expanded,
    } kind;
    union {
        Macro_Syntax_Kind* multiple;
    } data;
};


struct Macro_Syntax_Data {
    Macro_Syntax_Kind kind;
    union {
        Expression_Node* expression;
        Type* type;
        Macro_Syntax_Data* multiple;
        Array_Macro_Syntax_Data multiple_expanded;
    } data;
};


typedef struct {
    Array_Declaration_Pointer items;
} Struct_Type;

typedef struct {
    Array_Declaration_Pointer items;
} Union_Type;

typedef struct {
    Array_String items;
} Enum_Type;

typedef struct {
    size_t value;
} Number_Type;

typedef struct {
    Expression_Node* expression;
    Type* computed_result_type;
} TypeOf_Type;

typedef struct {
    Identifier identifier;
    Array_Macro_Syntax_Data arguments;
    Location location;

    Macro_Syntax_Data result;
} Run_Macro;

struct Type {
    Array_Directive directives;
    enum {
        Type_None,
        Type_Basic,
        Type_Pointer,
        Type_Procedure,
        Type_Array,
        Type_Internal,
        Type_Struct,
        Type_Union,
        Type_Enum,
        Type_Number,
        Type_TypeOf,
        Type_RegisterSize,
        Type_RunMacro,
    } kind;
    union {
        Basic_Type basic;
        Pointer_Type pointer;
        Procedure_Type procedure;
        BArray_Type array;
        Internal_Type internal;
        Struct_Type struct_;
        Union_Type union_;
        Enum_Type enum_;
        Number_Type number;
        TypeOf_Type type_of;
        Run_Macro run_macro;
    } data;
};

struct Statement_Node;
typedef struct Statement_Node Statement_Node;

struct Declaration {
    char* name;
    Type type;
    Location location;
};

Dynamic_Array_Def(Statement_Node*, Array_Statement_Node, array_statement_node_)
Dynamic_Array_Def(Expression_Node*, Array_Expression_Node, array_expression_node_)
Dynamic_Array_Def(Declaration, Array_Declaration, array_declaration_)

typedef struct {
    Array_Statement_Node statements;
} Block_Node;

typedef struct {
    enum {
        Number_Integer,
        Number_Decimal,
    } kind;
    union {
        size_t integer;
        double decimal;
    } value;
    Type* type;
} Number_Node;

typedef struct {
    char* value;
} String_Node;

typedef struct {
    bool value;
} Boolean_Node;

typedef struct {
    Type* type;
} Null_Node;

typedef struct {
    Expression_Node* condition;
    Expression_Node* if_expression;
    Expression_Node* else_expression;
    Location location;
} If_Node;

typedef struct {
    Expression_Node* condition;
    Expression_Node* inside;
    Location location;
} While_Node;

typedef enum {
    Operator_Add,
    Operator_Subtract,
    Operator_Multiply,
    Operator_Divide,
    Operator_Modulus,
    Operator_Equal,
    Operator_NotEqual,
    Operator_Greater,
    Operator_GreaterEqual,
    Operator_Less,
    Operator_LessEqual,
    Operator_Not,
    Operator_And,
    Operator_Or,
} Operator;

typedef struct {
    enum {
        Invoke_Standard,
        Invoke_Operator,
    } kind;
    union {
        Expression_Node* procedure;
        struct {
            Operator operator_;
            Type computed_operand_type;
        } operator_;
    } data;
    Array_Expression_Node arguments;
    Location location;
} Invoke_Node;

typedef struct {
    enum {
        Retrieve_Assign_Identifier,
        Retrieve_Assign_Parent,
        Retrieve_Assign_Array,
    } kind;
    union {
        Identifier identifier;
        struct {
            Expression_Node* expression;
            char* name;
            Type computed_parent_type;
        } parent;
        struct {
            Expression_Node* expression_outer;
            Expression_Node* expression_inner;
            Type computed_array_type;
        } array;
    } data;
    Type computed_result_type;
    Location location;
} Retrieve_Assign_Node;

typedef Retrieve_Assign_Node Retrieve_Node;

typedef struct {
    Array_Expression_Node expressions;
} Multi_Expression_Node;

typedef struct {
    Expression_Node* inner;
} Reference_Node;

typedef struct {
    Type type;
    Expression_Node* expression;
    Type computed_input_type;
    Location location;
} Cast_Node;

typedef struct {
    Type type;
    Array_Expression_Node arguments;
    Location location;
} Build_Node;

typedef struct {
    Type type;
    Location location;
} Init_Node;

typedef struct {
    Type type;
    Type computed_result_type;
    Location location;
} SizeOf_Node;

typedef struct {
    Type type;
    Type computed_result_type;
    Location location;
} LengthOf_Node;

typedef struct {
    Type wanted;
    Type given;
} IsType_Node;

struct Expression_Node {
    Array_Directive directives;
    enum {
        Expression_Block,
        Expression_Number,
        Expression_String,
        Expression_Invoke,
        Expression_RunMacro,
        Expression_Retrieve,
        Expression_If,
        Expression_While,
        Expression_Multi,
        Expression_Reference,
        Expression_Boolean,
        Expression_Null,
        Expression_Cast,
        Expression_Init,
        Expression_Build,
        Expression_SizeOf,
        Expression_LengthOf,
        Expression_IsType,
    } kind;
    union {
        Block_Node block;
        Number_Node number;
        String_Node string;
        Invoke_Node invoke;
        Run_Macro run_macro;
        Retrieve_Node retrieve;
        If_Node if_;
        While_Node while_;
        Multi_Expression_Node multi;
        Reference_Node reference;
        Boolean_Node boolean;
        Null_Node null;
        Cast_Node cast;
        Init_Node init;
        Build_Node build;
        SizeOf_Node size_of;
        LengthOf_Node length_of;
        IsType_Node is_type;
    } data;
};

typedef struct {
    Expression_Node* expression;
} Statement_Expression_Node;

typedef struct {
    Array_Declaration declarations;
    Expression_Node* expression;
} Statement_Declare_Node;

typedef Retrieve_Assign_Node Statement_Assign_Part;

Dynamic_Array_Def(Statement_Assign_Part, Array_Statement_Assign_Part, array_statement_assign_part_)

typedef struct {
    Array_Statement_Assign_Part parts;
    Expression_Node* expression;
} Statement_Assign_Node;

typedef struct {
    Expression_Node* expression;
    Location location;
} Statement_Return_Node;

struct Statement_Node {
    Array_Directive directives;
    enum {
        Statement_Expression,
        Statement_Declare,
        Statement_Assign,
        Statement_Return,
    } kind;
    union {
        Statement_Expression_Node expression;
        Statement_Declare_Node declare;
        Statement_Assign_Node assign;
        Statement_Return_Node return_;
    } data;
    Location statement_end_location;
};

typedef struct {
    Array_Declaration arguments;
    Array_Type returns;
    Expression_Node* body;
} Procedure_Node;

typedef struct {
    Array_String bindings;
    Macro_Syntax_Data data;
} Macro_Variant;

Dynamic_Array_Def(Macro_Variant, Array_Macro_Variant, array_macro_variant_)
Dynamic_Array_Def(Macro_Syntax_Kind, Array_Macro_Syntax_Kind, array_macro_syntax_kind_)

typedef struct {
    Array_Macro_Syntax_Kind arguments;
    Macro_Syntax_Kind return_;
    Array_Macro_Variant variants;
} Macro_Node;

typedef struct {
    Type type;
} Type_Node;

Dynamic_Array_Def(Item_Node, Array_Item_Node, array_item_node_)

typedef struct {
    Type type;
} Global_Node;

typedef struct {
    Number_Node expression;
} Constant_Node;

struct Item_Node {
    char* name;
    Array_Directive directives;
    enum {
        Item_Procedure,
        Item_Macro,
        Item_Type,
        Item_Global,
        Item_Constant,
    } kind;
    union {
        Procedure_Node procedure;
        Macro_Node macro;
        Type_Node type;
        Global_Node global;
        Constant_Node constant;
    } data;
};

typedef struct {
    char* path;
    size_t id;
    Array_Item_Node items;
} File_Node;

Dynamic_Array_Def(File_Node, Program, program_)

#endif
