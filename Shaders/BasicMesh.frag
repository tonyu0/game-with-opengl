#version 330

// input from vertex shader
in vec2 fragTexCoord;

// 与えられたテクスチャ座標にしたがってテクスチャから色を取得。
// ２Dテクスチャをサンプリングする特殊な型
// テクスチャ１枚しかバインドしないのでuniformをバインドする必要はない。
uniform sampler2D uTexture;
// output will stored in outColor
out vec4 outColor;

void main(){
    // uTextureをfragTexCoordを用いて塗る。
    outColor = texture(uTexture, fragTexCoord);
}
