#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdint.h>

namespace trix {
  using string = std::wstring;
  template<typename T> using r = std::shared_ptr<T>;
  template<typename T> using v = std::vector<T>;
  template<typename T> using vr = std::vector<r<T>>;

  namespace ast {

    class FQIdentifier {
    public:
      v<string> Identifiers;
    };

    enum class TypeCode {
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

    class ADeclStructItem {
    public:
      bool IsPrivate;
    };

    class DeclFunctionArgument {
    public:
      string Identifier;
      TypeRef Type;
    };

    enum class Operator {
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

    enum class ExprTypeCode {
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

    class DeclSymbol : public ADeclStructItem {
    public:
      string Identifier;
      TypeRef Type;
    };

    class DeclFunction : public ADeclStructItem {
    public:
      string Identifier;
      TypeRef Type;
      v<DeclFunctionArgument> Arguments;
      r<DeclFunctionBody> Body;
    };

    class ADeclNamespaceItem {
    public:
    };

    class DeclStruct : public ADeclNamespaceItem {
    public:
      bool IsPrivate;
      string Identifier;
      vr<ADeclStructItem> Items;
    };

    class DeclNamespaceImport : public ADeclNamespaceItem {
    public:
      ImportClause Import;
    };

    enum class CompilationUnitItemTypeCode {
      Namespace, Import
    };

    class ACompilationUnitItem {
    public:
      CompilationUnitItemTypeCode Type;
    };

    class DeclNamespace {
    public:
      FQIdentifier Identifier;
      v<r<ADeclNamespaceItem>> Items;
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
}
