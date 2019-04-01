// GLSL 3.3
#version 330

// ワールド行列、ビュー行列が描画時に渡ってくる
uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

// 頂点バッファのうち、0~2が頂点位置、3~5が法線の方向、6,7がuv座標
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

// フラグメントシェーダに渡す値
out vec2 fragTexCoord;
// ワールド空間での法線
out vec3 fragNormal;
// ワールド空間での座標
out vec3 fragWorldPos;

void main()
{
	// 同次座標へ変換
	vec4 pos = vec4(inPosition, 1.0);
	// ワールド空間へ
	pos = pos * uWorldTransform;
	// ワールド座標を一旦保存
	fragWorldPos = pos.xyz;
	// クリッピング空間に射影
	gl_Position = pos * uViewProj;

    // 法線
	// Transform normal into world space (w = 0)
    // 法線は位置ではないので、w成分は0
	fragNormal = (vec4(inNormal, 0.0f) * uWorldTransform).xyz;

	// Pass along the texture coordinate to frag shader
	fragTexCoord = inTexCoord;
}
