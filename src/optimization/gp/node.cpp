#include "yarl/optimization/gp/tree.hpp"

namespace yarl {
namespace gp {

Node::Node(void) {
  // general
  this->type = UINITI;
  this->parent = NULL;
  this->nth_child = UINITI;

  // constant
  this->nval = UINITI;

  // input
  this->input = "";

  // function
  this->fval = UINITI;
  this->arity = UINITI;
  this->children = {NULL, NULL};

  // evaluation
  this->data = VecX();
}

Node::~Node(void) {
  for (int i = 0; i < this->arity; i++) {
    if (this->children[i] != NULL) {
      delete this->children[i];
      this->children[i] = NULL;
    }
  }
}

void Node::setAsConstant(double constant) {
  // general
  this->type = CONST;
  this->parent = NULL;
  this->nth_child = UINITI;

  // constant
  this->nval = constant;

  // input
  this->input = "";

  // function
  this->fval = UINITI;
  this->arity = UINITI;
  this->children = {NULL, NULL};

  // evaluation
  this->data = VecX();
}

void Node::setAsInput(const std::string &input) {
  // general
  this->type = INPUT;
  this->parent = NULL;
  this->nth_child = UINITI;

  // constant
  this->nval = UINITI;

  // input
  this->input = input;

  // function
  this->fval = UINITI;
  this->arity = UINITI;
  this->children = {NULL, NULL};

  // evaluation
  this->data = VecX();
}

void Node::setAsFuncEval(int length) {
  // general
  this->type = FEVAL;
  this->parent = NULL;
  this->nth_child = UINITI;

  // constant
  this->nval = UINITI;

  // input
  this->input = "";

  // function
  this->fval = UINITI;
  this->arity = UINITI;
  this->children = {NULL, NULL};

  // evaluation
  this->data = VecX(length);
}

void Node::setAsUnaryFunc(int function_type) {
  // general
  this->type = UFUNC;
  this->parent = NULL;
  this->nth_child = UINITI;

  // constant
  this->nval = UINITI;

  // input
  this->input = "";

  // function
  this->fval = function_type;
  this->arity = 1;
  this->children = {NULL, NULL};

  // evaluation
  this->data = VecX();
}

void Node::setAsBinaryFunc(int function_type) {
  // general
  this->type = BFUNC;
  this->parent = NULL;
  this->nth_child = UINITI;

  // constant
  this->nval = UINITI;

  // input
  this->input = "";

  // function
  this->fval = function_type;
  this->arity = 2;
  this->children = {NULL, NULL};

  // evaluation
  this->data = VecX();
}

bool Node::isTermNode(void) const {
  if (this->type == CONST || this->type == INPUT || this->type == FEVAL) {
    return true;
  } else {
    return false;
  }
}

bool Node::isFuncNode(void) const {
  if (this->type == UFUNC || this->type == BFUNC) {
    return true;
  } else {
    return false;
  }
}

int Node::copyFrom(const Node &target) {
  // general
  this->type = target.type;
  this->parent = target.parent;
  this->nth_child = target.nth_child;

  // constant
  if (target.type == CONST) {
    this->nval = target.nval;
  }

  // input
  if (target.type == INPUT) {
    this->input = target.input;
  }

  // function
  if (target.type == UFUNC || target.type == BFUNC) {
    this->fval = target.fval;
    this->arity = target.arity;

    // this function does not copy the children, if you want that
    // use Node::deepCopyFrame() instead
  }

  // evaluation
  if (target.type == FEVAL) {
    this->data = target.data;
  }

  return 0;
}

int Node::deepCopyFrom(const Node &target) {
  // general
  this->type = target.type;
  this->parent = target.parent;
  this->nth_child = target.nth_child;

  // constant
  this->nval = target.nval;

  // input
  this->input = target.input;

  // function
  this->fval = target.fval;
  this->arity = target.arity;
  this->children = {NULL, NULL};
  for (int i = 0; i < target.arity; i++) {
    if (target.children[i] != NULL) {
      this->children[i] = new Node();
      this->children[i]->deepCopyFrom(*target.children[i]);
    }
  }

  // evaluation
  this->data = target.data;

  return 0;
}

bool Node::equals(const Node &target) {
  // pre-check
  if (this->type != target.type) {
    return false;
  }

  // constant
  if (this->type == CONST) {
    if (fltcmp(this->nval, target.nval) != 0) {
      return false;
    }
  }

  // input
  if (this->type == INPUT) {
    if (this->input.compare(target.input) != 0) {
      return false;
    }
  }

  // function
  if (this->type == UFUNC || target.type == BFUNC) {
    if (this->fval != target.fval) {
      return false;
    } else if (this->arity != target.arity) {
      return false;
    }
  }

  // evaluation
  if (this->type == FEVAL) {
    for (int i = 0; i < this->data.size(); i++) {
      if (fltcmp(this->data[i], target.data[i]) != 0) {
        return false;
      }
    }
  }

  return true;
}

bool Node::deepEquals(const Node &target) {
  int retval;

  if (this->isTermNode() && target.isTermNode()) {
    return this->equals(target);

  } else if (this->isFuncNode() && target.isFuncNode()) {
    if (this->equals(target) == false) {
      return false;
    }

    for (int i = 0; i < this->arity; i++) {
      retval = this->children[i]->deepEquals(*target.children[i]);
      if (retval == false) {
        return false;
      }
    }
  }

  return true;
}

std::string Node::toString(void) {
  std::ostringstream oss;

  // build node string
  if (this->type == CONST) {
    oss << "T[" << this->nval << "]";

  } else if (this->type == INPUT) {
    oss << "T[" << this->input << "]";

  } else if (this->type == UFUNC) {
    switch (this->fval) {
      case LOG: oss << "F[LOG]"; break;
      case EXP: oss << "F[EXP]"; break;
      case RAD: oss << "F[RAD]"; break;
      case SIN: oss << "F[SIN]"; break;
      case COS: oss << "F[COS]"; break;
    }
  } else if (this->type == BFUNC) {
    switch (this->fval) {
      case ADD: oss << "F[ADD]"; break;
      case SUB: oss << "F[SUB]"; break;
      case MUL: oss << "F[MUL]"; break;
      case DIV: oss << "F[DIV]"; break;
      case POW: oss << "F[POW]"; break;
    }
  }

  // copy and return node string
  return oss.str();
}

void Node::print(void) {
  std::cout << this->toString() << std::endl;
}

}  // end of gp namespace
}  // end of yarl namespace
