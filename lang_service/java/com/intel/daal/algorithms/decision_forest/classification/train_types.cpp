/* file: train_types.cpp */
/*******************************************************************************
* Copyright 2014-2019 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>

#include "daal.h"
#include "com_intel_daal_algorithms_decision_forest_classification_training_Parameter.h"
#include "com_intel_daal_algorithms_decision_forest_classification_training_TrainingResult.h"
#include "common_helpers.h"
#include "common_defines.i"

USING_COMMON_NAMESPACES()

namespace dfc  = decision_forest::classification;
namespace dfct = daal::algorithms::decision_forest::classification::training;

#include "com_intel_daal_algorithms_decision_forest_classification_training_ResultNumericTableId.h"
#define outOfBagErrorId      com_intel_daal_algorithms_decision_forest_classification_training_ResultNumericTableId_outOfBagErrorId
#define variableImportanceId com_intel_daal_algorithms_decision_forest_classification_training_ResultNumericTableId_variableImportanceId
#define outOfBagErrorPerObservationId \
    com_intel_daal_algorithms_decision_forest_classification_training_ResultNumericTableId_outOfBagErrorPerObservationId
#include "com_intel_daal_algorithms_classifier_training_TrainingResultId.h"
#define ModelResult com_intel_daal_algorithms_classifier_training_TrainingResultId_Model

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cGetNTrees
* Signature: (J)J
*/
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cGetNTrees(JNIEnv *, jobject, jlong parAddr)
{
    return (jlong)(*(dfct::Parameter *)parAddr).nTrees;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cSetNTrees
* Signature: (JJ)V
*/
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cSetNTrees(JNIEnv *, jobject, jlong parAddr,
                                                                                                                    jlong value)
{
    (*(dfct::Parameter *)parAddr).nTrees = value;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cSetObservationsPerTreeFraction
* Signature: (JD)V
*/
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cSetObservationsPerTreeFraction(
    JNIEnv *, jobject, jlong parAddr, jdouble value)
{
    (*(dfct::Parameter *)parAddr).observationsPerTreeFraction = value;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cGetObservationsPerTreeFraction
* Signature: (J)D
*/
JNIEXPORT jdouble JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cGetObservationsPerTreeFraction(
    JNIEnv *, jobject, jlong parAddr)
{
    return (jdouble)(*(dfct::Parameter *)parAddr).observationsPerTreeFraction;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cGetFeaturesPerNode
* Signature: (J)J
*/
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cGetFeaturesPerNode(JNIEnv *, jobject,
                                                                                                                              jlong parAddr)
{
    return (jlong)(*(dfct::Parameter *)parAddr).featuresPerNode;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cSetFeaturesPerNode
* Signature: (JJ)V
*/
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cSetFeaturesPerNode(JNIEnv *, jobject,
                                                                                                                             jlong parAddr,
                                                                                                                             jlong value)
{
    (*(dfct::Parameter *)parAddr).featuresPerNode = value;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cGetMaxTreeDepth
* Signature: (J)J
*/
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cGetMaxTreeDepth(JNIEnv *, jobject,
                                                                                                                           jlong parAddr)
{
    return (jlong)(*(dfct::Parameter *)parAddr).maxTreeDepth;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cSetMaxTreeDepth
* Signature: (JJ)V
*/
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cSetMaxTreeDepth(JNIEnv *, jobject,
                                                                                                                          jlong parAddr, jlong value)
{
    (*(dfct::Parameter *)parAddr).maxTreeDepth = value;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cGetMinObservationsInLeafNode
* Signature: (J)J
*/
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cGetMinObservationsInLeafNode(JNIEnv *,
                                                                                                                                        jobject,
                                                                                                                                        jlong parAddr)
{
    return (jlong)(*(dfct::Parameter *)parAddr).minObservationsInLeafNode;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cSetMinObservationsInLeafNode
* Signature: (JJ)V
*/
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cSetMinObservationsInLeafNode(JNIEnv *,
                                                                                                                                       jobject,
                                                                                                                                       jlong parAddr,
                                                                                                                                       jlong value)
{
    (*(dfct::Parameter *)parAddr).minObservationsInLeafNode = value;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cGetSeed
* Signature: (J)I
*/
JNIEXPORT jint JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cGetSeed(JNIEnv *, jobject, jlong parAddr)
{
    return (jint)(*(dfct::Parameter *)parAddr).seed;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cSetSeed
* Signature: (JI)V
*/
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cSetSeed(JNIEnv *, jobject, jlong parAddr,
                                                                                                                  jint value)
{
    (*(dfct::Parameter *)parAddr).seed = value;
}

/*
 * Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
 * Method:    cSetEngine
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cSetEngine(JNIEnv * env, jobject thisObj,
                                                                                                                    jlong cParameter,
                                                                                                                    jlong engineAddr)
{
    (((dfct::Parameter *)cParameter))->engine = staticPointerCast<engines::BatchBase, AlgorithmIface>(*(SharedPtr<AlgorithmIface> *)engineAddr);
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cSetImpurityThreshold
* Signature: (JD)V
*/
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cSetImpurityThreshold(JNIEnv *, jobject,
                                                                                                                               jlong parAddr,
                                                                                                                               jdouble value)
{
    (*(dfct::Parameter *)parAddr).impurityThreshold = value;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cGetImpurityThreshold
* Signature: (J)D
*/
JNIEXPORT jdouble JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cGetImpurityThreshold(JNIEnv *, jobject,
                                                                                                                                  jlong parAddr)
{
    return (jdouble)(*(dfct::Parameter *)parAddr).impurityThreshold;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cSetResultsToCompute
* Signature: (JJ)V
*/
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cSetResultsToCompute(JNIEnv *, jobject,
                                                                                                                              jlong parAddr,
                                                                                                                              jlong value)
{
    (*(dfct::Parameter *)parAddr).resultsToCompute = value;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cGetResultsToCompute
* Signature: (J)J
*/
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cGetResultsToCompute(JNIEnv *, jobject,
                                                                                                                               jlong parAddr)
{
    return (jlong)(*(dfct::Parameter *)parAddr).resultsToCompute;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cGetVariableImportanceMode
* Signature: (J)I
*/
JNIEXPORT jint JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cGetVariableImportanceMode(JNIEnv *, jobject,
                                                                                                                                    jlong parAddr)
{
    return (jint)(*(dfct::Parameter *)parAddr).varImportance;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_Parameter
* Method:    cSetVariableImportanceMode
* Signature: (JI)V
*/
JNIEXPORT void JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_Parameter_cSetVariableImportanceMode(JNIEnv *, jobject,
                                                                                                                                    jlong parAddr,
                                                                                                                                    jint value)
{
    (*(dfct::Parameter *)parAddr).varImportance = decision_forest::training::VariableImportanceMode(value);
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_TrainingResult
* Method:    cGetResult
* Signature: (JI)J
*/
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_TrainingResult_cGetResult(JNIEnv *, jobject,
                                                                                                                          jlong algAddr, jint cmode)
{
    SerializationIfacePtr * ptr = new SerializationIfacePtr();

    if (cmode == jBatch)
    {
        SharedPtr<classifier::training::Batch> alg =
            staticPointerCast<classifier::training::Batch, AlgorithmIface>(*(SharedPtr<AlgorithmIface> *)algAddr);
        *ptr = alg->getResult();
    }
    return (jlong)ptr;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_TrainingResult
* Method:    cGetModel
* Signature: (JI)J
*/
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_TrainingResult_cGetModel(JNIEnv *, jobject thisObj,
                                                                                                                         jlong resAddr, jint id)
{
    dfc::ModelPtr * m = new dfc::ModelPtr();
    classifier::training::ResultPtr res =
        services::staticPointerCast<classifier::training::Result, SerializationIface>(*((SerializationIfacePtr *)resAddr));

    switch (id)
    {
    case ModelResult: *m = services::staticPointerCast<dfc::Model, classifier::Model>(res->get(classifier::training::model)); break;
    default: break;
    }
    return (jlong)m;
}

/*
* Class:     com_intel_daal_algorithms_decision_forest_classification_training_TrainingResult
* Method:    cGetResultTable
* Signature: (JI)J
*/
JNIEXPORT jlong JNICALL Java_com_intel_daal_algorithms_decision_1forest_classification_training_TrainingResult_cGetResultTable(JNIEnv *,
                                                                                                                               jobject thisObj,
                                                                                                                               jlong resAddr, jint id)
{
    NumericTablePtr * pTbl = new NumericTablePtr();
    dfct::ResultPtr res    = services::staticPointerCast<dfct::Result, SerializationIface>(*((SerializationIfacePtr *)resAddr));

    switch (id)
    {
    case outOfBagErrorId:
    case variableImportanceId:
    case outOfBagErrorPerObservationId: *pTbl = res->get(dfct::ResultNumericTableId(id)); break;
    default: break;
    }
    return (jlong)pTbl;
}
