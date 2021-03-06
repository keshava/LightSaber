#pragma once

#include <vector>

#include "Predicate.h"
#include "cql/expressions/Expression.h"

/*
 * \brief This class is used ofr combining predicates with OR.
 *
 * */

class ORPredicate : public Predicate {
 public:
  ORPredicate(std::vector<Predicate *> &predicates) : m_predicates(predicates) {};
  std::vector<Predicate *> &getPredicates() { return m_predicates; }
  std::string toSExpr() const override {
    std::string s;
    for (unsigned long i = 0; i < m_predicates.size(); ++i) {
      s.append("(").append(m_predicates[i]->toSExpr()).append(")");
      if (i != m_predicates.size() - 1)
        s.append(" OR ");
    }
    return s;
  }
  std::string toSExprForCodeGen() const override {
    std::string s;
    for (unsigned long i = 0; i < m_predicates.size(); ++i) {
      s.append("(").append(m_predicates[i]->toSExprForCodeGen()).append(")");
      if (i != m_predicates.size() - 1)
        s.append(" OR ");
    }
    return s;
  }
  explicit operator std::string() const {
    std::string s;
    for (unsigned long i = 0; i < m_predicates.size(); ++i) {
      s.append("(").append(m_predicates[i]->toSExpr()).append(")");
      if (i != m_predicates.size() - 1)
        s.append(" OR ");
    }
    return s;
  }
  int getNumberOfPredicates() const override { return (int) m_predicates.size(); };
  ~ORPredicate() override = default;
 private:
  std::vector<Predicate *> &m_predicates;
};

