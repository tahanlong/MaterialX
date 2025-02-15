//
// TM & (c) 2017 Lucasfilm Entertainment Company Ltd. and Lucasfilm Ltd.
// All rights reserved.  See LICENSE.txt for license.
//

#ifndef MATERIALX_TRANSFORMVECTORNODEGLSL_H
#define MATERIALX_TRANSFORMVECTORNODEGLSL_H

#include <MaterialXGenGlsl/GlslShaderGenerator.h>

namespace MaterialX
{

/// Implementation of transformsvector node for GLSL
class TransformVectorNodeGlsl : public GlslImplementation
{
public:
    static ShaderNodeImplPtr create();

    void createVariables(const ShaderNode& node, GenContext& context, Shader& shader) const override;

    void emitFunctionCall(const ShaderNode& node, GenContext& context, ShaderStage& stage) const override;

protected:
    virtual const string& getMatrix(const string& fromSpace, const string& toSpace) const;
    virtual string getHomogeneousCoordinate(const ShaderInput* in, GenContext& context) const;

    static const string WORLD_MATRIX;
    static const string WORLD_TRANSPOSE_MATRIX;
    static const string WORLD_INVERSE_MATRIX;
    static const string WORLD_INVERSE_TRANSPOSE_MATRIX;
};

} // namespace MaterialX

#endif
