#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform float iTime;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main() {
    // Texel color fetching from texture sampler
    vec4 source = texture(texture0, fragTexCoord);
    
    if (length(source)<1.3) {
        source = mix(source, vec4(0.0588, 0.0588, 0.0588, 1.0), .8+sin(iTime*5+fragTexCoord.y*10+fragTexCoord.x*10)*.6);
    } else {
        source = vec4(1);
    }

    // Calculate final fragment color
    finalColor = source;
}