// OpenGL 3.3
#version 330

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;
// input data is assigned to inPosition
// VertexArrayクラスのglVertexAttribPointerの番号に対応
layout(location=0) in vec3 inPosition;
layout(location=1) in vec3 inNormal;
layout(location=2) in vec2 inTexCoord;

// フラグメントシェーダーにもUV座標を渡す。
out vec2 fragTexCoord;

void main(){
    // gl_Position - store output data (adding w component)
    // 位置座標を同時座標へ
    vec4 pos = vec4(inPosition,1.0);
    // 位置をワールド空間へ、その後クリップ空間へ
    gl_Position = pos * uWorldTransform * uViewProj;
    
    // フラグメントシェーダーにテクスチャの座標も送る。
    fragTexCoord = inTexCoord;
}
