#include <memory>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <RMLPositionFlags.h>
#include <RMLPositionInputParameters.h>
#include <RMLPositionOutputParameters.h>
#include <ReflexxesAPI.h>

namespace py = pybind11;

using Array = std::vector<double>;
using BoolArray = std::vector<bool>;

PYBIND11_PLUGIN(reflexxes_motion_library) {
  py::module m("reflexxes_motion_library", "Reflexxes Type II Motion Library");

  py::class_<ReflexxesAPI>(m, "ReflexxesAPI")
      .def(py::init<const unsigned int &, const double &,
                    const unsigned int &>(),
           py::arg("degrees_of_freedom"), py::arg("cycle_time_in_seconds"),
           py::arg("number_of_additional_threads") = 0)
      .def("position", &ReflexxesAPI::RMLPosition)
      .def("velocity", &ReflexxesAPI::RMLVelocity);

  py::class_<RMLPositionInputParameters>(m, "PositionInputParameters")
      .def(py::init<const unsigned int>(), py::arg("degrees_of_freedom"))
      .def_property(
          "selection_vector",
          [](RMLPositionInputParameters &instance) {
            BoolArray arr(instance.NumberOfDOFs);
            for (int i = 0; i < instance.NumberOfDOFs; ++i) {
              arr[i] = instance.GetSelectionVectorElement(i);
            }
            return arr;
          },
          [](RMLPositionInputParameters &instance, const BoolArray &arr) {
            for (int i = 0; i < instance.NumberOfDOFs; ++i) {
              instance.SetSelectionVectorElement(arr[i], i);
            }
          })
      .def_property("target_position_vector",
                    [](RMLPositionInputParameters &instance) {
                      Array arr(instance.NumberOfDOFs);
                      instance.GetTargetPositionVector(
                          arr.data(), arr.size() * sizeof(double));
                      return arr;
                    },
                    [](RMLPositionInputParameters &instance, const Array &arr) {
                      instance.SetTargetPositionVector(arr.data());
                    })
      .def_property("target_velocity_vector",
                    [](RMLPositionInputParameters &instance) {
                      Array arr(instance.NumberOfDOFs);
                      instance.GetTargetVelocityVector(
                          arr.data(), arr.size() * sizeof(double));
                      return arr;
                    },
                    [](RMLPositionInputParameters &instance, const Array &arr) {
                      instance.SetTargetVelocityVector(arr.data());
                    })
      .def_property("current_velocity_vector",
                    [](RMLPositionInputParameters &instance) {
                      Array arr(instance.NumberOfDOFs);
                      instance.GetCurrentVelocityVector(
                          arr.data(), arr.size() * sizeof(double));
                      return arr;
                    },
                    [](RMLPositionInputParameters &instance, const Array &arr) {
                      instance.SetCurrentVelocityVector(arr.data());
                    })
      .def_property("current_acceleration_vector",
                    [](RMLPositionInputParameters &instance) {
                      Array arr(instance.NumberOfDOFs);
                      instance.GetCurrentAccelerationVector(
                          arr.data(), arr.size() * sizeof(double));
                      return arr;
                    },
                    [](RMLPositionInputParameters &instance, const Array &arr) {
                      instance.SetCurrentAccelerationVector(arr.data());
                    })
      .def_property("current_position_vector",
                    [](RMLPositionInputParameters &instance) {
                      Array arr(instance.NumberOfDOFs);
                      instance.GetCurrentPositionVector(
                          arr.data(), arr.size() * sizeof(double));
                      return arr;
                    },
                    [](RMLPositionInputParameters &instance, const Array &arr) {
                      instance.SetCurrentPositionVector(arr.data());
                    })
      .def_property("max_velocity_vector",
                    [](RMLPositionInputParameters &instance) {
                      Array arr(instance.NumberOfDOFs);
                      instance.GetMaxVelocityVector(
                          arr.data(), arr.size() * sizeof(double));
                      return arr;
                    },
                    [](RMLPositionInputParameters &instance, const Array &arr) {
                      instance.SetMaxVelocityVector(arr.data());
                    })
      .def_property("max_acceleration_vector",
                    [](RMLPositionInputParameters &instance) {
                      Array arr(instance.NumberOfDOFs);
                      instance.GetMaxAccelerationVector(
                          arr.data(), arr.size() * sizeof(double));
                      return arr;
                    },
                    [](RMLPositionInputParameters &instance, const Array &arr) {
                      instance.SetMaxAccelerationVector(arr.data());
                    })
      .def_property("max_jerk_vector",
                    [](RMLPositionInputParameters &instance) {
                      Array arr(instance.NumberOfDOFs);
                      instance.GetMaxJerkVector(arr.data(),
                                                arr.size() * sizeof(double));
                      return arr;
                    },
                    [](RMLPositionInputParameters &instance, const Array &arr) {
                      instance.SetMaxJerkVector(arr.data());
                    });

  py::class_<RMLPositionOutputParameters>(m, "PositionOutputParameters")
      .def(py::init<const unsigned int>(), py::arg("degrees_of_freedom"))
      .def_property_readonly("new_velocity_vector",
                             [](RMLPositionOutputParameters &instance) {
                               Array arr(instance.NumberOfDOFs);
                               instance.GetNewVelocityVector(
                                   arr.data(), arr.size() * sizeof(double));
                               return arr;
                             })
      .def_property_readonly("new_acceleration_vector",
                             [](RMLPositionOutputParameters &instance) {
                               Array arr(instance.NumberOfDOFs);
                               instance.GetNewAccelerationVector(
                                   arr.data(), arr.size() * sizeof(double));
                               return arr;
                             })
      .def_property_readonly("new_position_vector",
                             [](RMLPositionOutputParameters &instance) {
                               Array arr(instance.NumberOfDOFs);
                               instance.GetNewPositionVector(
                                   arr.data(), arr.size() * sizeof(double));
                               return arr;
                             })
      .def("is_trajectory_phase_synchronized",
                             [](RMLPositionOutputParameters &instance) {
                               return instance.IsTrajectoryPhaseSynchronized();
                             })
      .def("was_a_complete_computation_performed_during_the_last_cycle",
                             [](RMLPositionOutputParameters &instance) {
                               return instance.WasACompleteComputationPerformedDuringTheLastCycle();
                             });

  py::class_<RMLPositionFlags>(m, "PositionFlags").def(py::init<>());

  py::enum_<ReflexxesAPI::RMLResultValue>(m, "ResultValue")
      .value("WORKING", ReflexxesAPI::RMLResultValue::RML_WORKING)
      .value("FINAL_STATE_REACHED",
             ReflexxesAPI::RMLResultValue::RML_FINAL_STATE_REACHED)
      .value("ERROR", ReflexxesAPI::RMLResultValue::RML_ERROR)
      .value("ERROR_INVALID_INPUT_VALUES",
             ReflexxesAPI::RMLResultValue::RML_ERROR_INVALID_INPUT_VALUES)
      .value("ERROR_EXECUTION_TIME_CALCULATION",
             ReflexxesAPI::RMLResultValue::RML_ERROR_EXECUTION_TIME_CALCULATION)
      .value("ERROR_SYNCHRONIZATION",
             ReflexxesAPI::RMLResultValue::RML_ERROR_SYNCHRONIZATION)
      .value("ERROR_NUMBER_OF_DOFS",
             ReflexxesAPI::RMLResultValue::RML_ERROR_NUMBER_OF_DOFS)
      .value("ERROR_NO_PHASE_SYNCHRONIZATION",
             ReflexxesAPI::RMLResultValue::RML_ERROR_NO_PHASE_SYNCHRONIZATION)
      .value("ERROR_NULL_POINTER",
             ReflexxesAPI::RMLResultValue::RML_ERROR_NULL_POINTER)
      .value("RML_ERROR_EXECUTION_TIME_TOO_BIG",
             ReflexxesAPI::RMLResultValue::RML_ERROR_EXECUTION_TIME_TOO_BIG)
      .value("ERROR_USER_TIME_OUT_OF_RANGE",
             ReflexxesAPI::RMLResultValue::RML_ERROR_USER_TIME_OUT_OF_RANGE)
      .export_values();

  return m.ptr();
}
