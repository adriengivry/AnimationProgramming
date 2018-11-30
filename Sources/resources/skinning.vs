
/////////////////////
// INPUT VARIABLES //
/////////////////////
in lowp vec3 inputPosition;
in lowp vec3 normal;
in lowp vec4 boneIndices;
in lowp vec4 boneWeights;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
smooth out vec2 texCoord;
smooth out vec3 outNormal;
smooth out vec4 outWeightColor;

uniform SceneMatrices
{
	uniform mat4 projectionMatrix;
} sm;

uniform mat4 modelViewMatrix;

uniform SkinningMatrices
{
	uniform mat4 mat[64];
} skin;

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
void main(void)
{
	vec4 defaultPos = vec4(inputPosition, 1.0f);
	vec4 animationPos = vec4(0, 0, 0, 1);
	vec3 defaultNormal = normal;
	vec3 animationNormal = vec3(0, 0, 0);

	for (int i = 0; i < 4; ++i)
	{
		animationPos += boneWeights[i] * (defaultPos * skin.mat[int(boneIndices[i])]);
		animationNormal += boneWeights[i] * (defaultNormal * mat3(skin.mat[int(boneIndices[i])]));
	}

	gl_Position = sm.projectionMatrix * (modelViewMatrix * vec4(animationPos.xyz, 1.0f));
	outNormal = normalize(mat3(modelViewMatrix) * animationNormal);

	/*
		This is what I want (But I don't)

		0, 0, 0 --> 0
		0, 0, 1 --> 0.25
		0, 1, 0 --> 0.5
		1, 0, 0 --> 0.75
		1, 1, 1 --> 1
	*/

	float w = boneWeights.x;
	float r = 0.9f;
	float g = 0.0f;
	float b = 0.0f;

	outWeightColor = vec4(vec3(r, g, b) * w, 0.5f);
}
