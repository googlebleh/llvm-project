//===--- RxNetworkCheck.cpp - clang-tidy ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "RxNetworkCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace bugprone {

void RxNetworkCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  const auto socketCall =
      callExpr(callee(functionDecl(hasName("socket"))));
  Finder->addMatcher(socketCall.bind("x"), this);
}

// #define JOE
#ifdef JOE

void RxNetworkCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedCall = Result.Nodes.getNodeAs<CallExpr>("x");
  const auto *functionDecl = MatchedCall->getDirectCallee();
  if (functionDecl and functionDecl->getIdentifier() and functionDecl->getName().equals("socket")) {
    diag(functionDecl->getLocation(), "function %0 is socket") << functionDecl;
  } else {
    diag(functionDecl->getLocation(), "function %0 is not socket") << functionDecl;
  }
}

#else

void RxNetworkCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const CallExpr *socketCall = Result.Nodes.getNodeAs<CallExpr>("x");
  diag(socketCall->getBeginLoc(), "got a call to socket");

  // const auto *funcCall = Result.Nodes.getNodeAs<CallExpr>("x");
  // const auto *functionDecl = funcCall->getDirectCallee();
  // for (auto it = child; funcCall.children()
  // for (auto it = v.begin(); it != v.end(); it++) {
  //   *it;
  // }

  // if (MatchedDecl->getIdentifier() and MatchedDecl->getName().startswith("socket")) {
  //   diag(MatchedDecl->getLocation(), "function %0 is socket()")
  //     << MatchedDecl;
  // } else {
  //   diag(MatchedDecl->getLocation(), "function %0 is not socket()")
  //     << MatchedDecl;
  // }

}

#endif

} // namespace bugprone
} // namespace tidy
} // namespace clang
