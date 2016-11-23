#ifndef __AST_H__
#define __AST_H__

#include <wstring>

namespace trix {

  class FQIdentifier {
  public:
    v<wstring> Identifiers;
  }

  class ImportClause {
  public:
    r<FQIdentifier> Namespace;
    r<FQIdentifier> Resource;
  }

  class DeclStructItem {
  public:
    bool IsPrivate;
  }

  class DeclFunctionArgument {
  public:
    wstring Identifier;
    r<TypeRef> Type;
  }

  enum TypeCode {
  }

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
  }

  enum ExprTypeCode {
    SymbolRef,
    NAry
  }

  class LiteralExpr {
  public:
    TypeCode Code;
    union {
      int64_t IntegerValue;
      float32_t FloatValue;
      uint16_t CharValue;
      wstring StringValue;
    };
  }

  class SymbolRefExpr : public Expr {
  public:
    r<FQIdentifier> Identifier;
  }

  class NAryExpr : public Expr {
  public:
    Operator Operator;
    v<Expr> Expressions;
  }

  class Expr {
  public:
    ExprTypeCode Type;
  }

  class DeclFunctionBody {
  public:
    v<Expr> Expressions;
  }

  class DeclSymbol : public DeclStructItem {
  public:
    wstring Identifier;
  }

  class DeclFunction : public DeclSymbol {
  public:
    r<TypeRef> Type;
    v<DeclFunctionArgument> Arguments;
    r<DeclFunctionBody> Body;
  }

  class DeclStruct {
  public:
    bool IsPrivate;
    wstring Identifier;
    v<DeclStructItem> Items;
  }

  class DeclNamespaceItem {
  public:
    r<ImportClause> Import;
    r<DeclNamespace> Namespace;
  }

  class DeclNamespace {
  public:
    r<FQIdentifier> Identifier;
    v<DeclNamespaceItem> Items;
  }
}

#endif /* end of include guard: __AST_H__ */
