#ifndef __AST_H__
#define __AST_H__

#include <string>
#include <vector>
#include <memory>
#include <stdint.h>

namespace trix {

  template<typename T> using v = std::vector<T>;
  template<typename T> using r = std::shared_ptr<T>;
  using string = std::wstring;

  class FQIdentifier {
  public:
    v<string> Identifiers;
  };

  enum TypeCode {
    Boolean,
    Byte,
    Char,
    DateTime,
    Double,
    GenericObject,
    Int16,
    Int32,
    Int64,
    Object,
    SByte,
    Single,
    String,
    UInt16,
    UInt32,
    UInt64
  };

  class TypeRef {
  public:
    TypeCode Type;
    v<TypeRef> GenericArguments;
    FQIdentifier Identifier;
  };

  class ImportClause {
  public:
    FQIdentifier Namespace;
    FQIdentifier Resource;
  };

  class DeclStructItem {
  public:
    bool IsPrivate;
  };

  class DeclFunctionArgument {
  public:
    string Identifier;
    TypeRef Type;
  };

  enum Operator {
    Index,
    Call,
    Assoc,
    MemberAccess,
    PatternMatch,
    Not,
    Xor,
    And,
    Or,
    Add,
    Subtract,
    Product,
    Divide,
    Modulus,
    BitAnd,
    BitOr,
    BitXor,
    BitNot // Add unary, and binary and n-ary
  };

  enum ExprTypeCode {
    Literal,
    SymbolRef,
    NAry
  };

  class AExpr {
  public:
    ExprTypeCode Type;
  };

  class LiteralExpr : public AExpr {
  public:
    TypeCode Code;
    int64_t IntegerValue;
    double FloatValue;
    uint16_t CharValue;
    string StringValue;
  };

  class SymbolRefExpr : public AExpr {
  public:
    FQIdentifier Identifier;
  };

  class NAryExpr : public AExpr {
  public:
    Operator Operator;
    v<AExpr> Expressions;
  };

  class DeclFunctionBody {
  public:
    v<AExpr> Expressions;
  };

  class DeclSymbol : public DeclStructItem {
  public:
    string Identifier;
  };

  class DeclFunction : public DeclSymbol {
  public:
    TypeRef Type;
    v<DeclFunctionArgument> Arguments;
    r<DeclFunctionBody> Body;
  };

  class DeclStruct {
  public:
    bool IsPrivate;
    string Identifier;
    v<DeclStructItem> Items;
  };

  class ADeclNamespaceItem {
  public:
  };

  class DeclNamespaceImport : public ADeclNamespaceItem {
  public:
    ImportClause Import;
  };

  enum CompilationUnitItemTypeCode {
    Namespace, Import
  };

  class ACompilationUnitItem {
  public:
    CompilationUnitItemTypeCode Type;
  };

  class DeclNamespace {
  public:
    FQIdentifier Identifier;
    v<ADeclNamespaceItem> Items;
  };

  class DeclNamespaceNamespace : public ADeclNamespaceItem {
  public:
    DeclNamespace Namespace;
  };

  class CompilationUnitNamespace : public ACompilationUnitItem {
  public:
    DeclNamespace Namespace;
  };

  class CompilationUnitImport : public ACompilationUnitItem {
  public:
    ImportClause Import;
  };

  class CompilationUnit {
  public:
    v<ACompilationUnitItem> Items;
  };
}

#endif /* end of include guard: __AST_H__ */
