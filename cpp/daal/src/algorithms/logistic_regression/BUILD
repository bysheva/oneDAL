package(default_visibility = ["//visibility:public"])
load("@onedal//dev/bazel:daal.bzl", "daal_module")

daal_module(
    name = "kernel",
    auto = True,
    opencl = True,
    deps = [
        "@onedal//cpp/daal:core",
        "@onedal//cpp/daal:sycl",
        "@onedal//cpp/daal/src/algorithms/classifier:kernel",
        "@onedal//cpp/daal/src/algorithms/objective_function:kernel",
        "@onedal//cpp/daal/src/algorithms/objective_function/logistic_loss:kernel",
        "@onedal//cpp/daal/src/algorithms/objective_function/cross_entropy_loss:kernel",
    ],
)
