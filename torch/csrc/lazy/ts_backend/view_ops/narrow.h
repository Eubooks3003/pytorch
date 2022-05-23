#pragma once

#include <torch/csrc/lazy/ts_backend/ts_node.h>

namespace torch {
namespace lazy {

class TORCH_API Narrow : public TsNode {
 public:
  static OpKind ClassOpKind() {
    return OpKind(at::aten::narrow);
  }

  Narrow(
      const Value& input,
      c10::ArrayRef<int64_t> base_indices,
      c10::ArrayRef<int64_t> sizes);

  bool CanBeReused(
      const Value& input,
      c10::ArrayRef<int64_t> base_indices,
      c10::ArrayRef<int64_t> sizes) const {
    size_t i = 0;
    return (
        operand(i++) == input &&
        base_indices_ == base_indices &&
        sizes_ == sizes);
  }

  std::string ToString() const override;

  const std::vector<int64_t>& base_indices() const {
    return base_indices_;
  }

  const std::vector<int64_t>& sizes() const {
    return sizes_;
  }

 private:
  std::vector<int64_t> base_indices_;
  std::vector<int64_t> sizes_;
};

} // namespace lazy
} // namespace torch
