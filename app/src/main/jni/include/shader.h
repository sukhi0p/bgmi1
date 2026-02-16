
//=================================||•• FOR YELLOW COLOR ••||===================================••||============================
		const char *YellowBodyColor =
        ( "#version 310 es\n"
        "\n"
        "precision mediump float;\n"        
        "\n"
        "precision highp float;\n"        
        "\n"
        "out vec4 fragColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "vec3 yellowColor = vec3(1.0, 1.0, 0.0);\n"  // Changed to yellow
        "fragColor = vec4(yellowColor, 0.7);\n"
        "}\n");

//=================================||•• FOR GREEN COLOR ••||===================================

        
const char *GreenBodyColor = 
    "#version 310 es\n"
    "precision mediump float;\n"
    "out vec4 fragColor;\n"
    "void main() {\n"
    "    fragColor = vec4(0.0, 1.0, 0.0, 0.7); // Green color\n"
    "}\n";
		

//=================================||•• FOR RBG COLOR ••||===================================
	/*	const char *CyanBodyColor =
        ( "#version 310 es\n"
        "\n"
        "precision mediump float;\n"        
        "\n"
        "precision highp float;\n"        
        "\n"
        "out vec4 fragColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "vec3 colors[7];\n"
        "colors[0] = vec3(1.0, 0.0, 0.0);\n"
        "colors[1] = vec3(1.0, 0.5, 0.0);\n"
        "colors[2] = vec3(1.0, 1.0, 0.0);\n"
        "colors[3] = vec3(0.0, 1.0, 0.0);\n"
        "colors[4] = vec3(0.0, 0.0, 1.0);\n"
        "colors[5] = vec3(0.5, 0.0, 1.0);\n"
        "colors[6] = vec3(1.0, 0.0, 1.0);\n"

        // Determine if the movement is left-to-right or right-to-left
        "float t = mod(gl_FragCoord.x / 100.0, 1.0);\n"
        
        // Check if the direction is left to right or right to left
        "float movementDirection = gl_FragCoord.x > 0.5 ? 1.0 : -1.0;\n"

        // Apply different logic based on the movement direction
        "int index;\n"
        "if (movementDirection > 0.0) {\n" // Left to right
        "    index = int(t * 7.0);\n"
        "} else {\n" // Right to left
        "    index = int((1.0 - t) * 7.0);\n"
        "}\n"
        
        "vec3 color = mix(colors[index], colors[(index + 1) % 7], fract(t * 7.0));\n"
        "vec3 hdrColor = color * 100.0;\n"
        "vec3 finalColor = hdrColor + color;\n"
        "fragColor = vec4(finalColor, 0.7);\n"
        "}\n");
		*/
		
		// ranbow body
	const char *CyanBodyColor =
    "#version 310 es\n"
    "precision highp float;\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main() {\n"
    "    vec2 uv = gl_FragCoord.xy / vec2(1080.0, 1920.0); // screen resolution\n"
    "\n"
    "    // Time-independent gradient across screen\n"
    "    float t = uv.x + uv.y;\n"
    "\n"
    "    // Create rainbow using sine waves\n"
    "    float r = 0.5 + 0.5 * sin(6.2831 * t + 0.0);\n"
    "    float g = 0.5 + 0.5 * sin(6.2831 * t + 2.0944);\n"
    "    float b = 0.5 + 0.5 * sin(6.2831 * t + 4.1888);\n"
    "\n"
    "    vec3 color = vec3(r, g, b);\n"
    "\n"
    "    // Add glow effect\n"
    "    color *= 1.5 + 0.5 * sin(gl_FragCoord.x * 0.01 + gl_FragCoord.y * 0.01);\n"
    "\n"
    "    // Final output with slight transparency\n"
    "    fragColor = vec4(color, 0.8);\n"
    "}\n";
		
		
		
		
		
		
		
//=================================||•• VECHALE ••||===================================

const char *Vechale =
        ( "#version 310 es\n"
        "\n"
        "precision mediump float;\n"
        "\n"
        "out vec4 fragColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "fragColor = vec4(0.0, 0.6, 1.0, 0.8);\n"
        "}\n");
		
//=================================||•• FOR BLACK COLOR ••||===================================
/*
/// black sky
const char *BlackBodyColor =
    ( "#version 310 es\n"
    "\n"
    "precision mediump float;\n"        
    "\n"
    "precision highp float;\n"        
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "vec3 blackColor = vec3(0.0, 0.0, 0.0); // Changed to black\n" //Changed to Black
    "fragColor = vec4(blackColor, 1.0);\n"
    "}\n");
	
	*/
	
	 ///// ranbow sky
	const char *BlackBodyColor =
    ( "#version 310 es\n"
    "precision mediump float;\n"
    "precision highp float;\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main() {\n"
    "    vec2 uv = gl_FragCoord.xy / vec2(1080.0, 1920.0);\n"
    "\n"
    "    float t = uv.x + uv.y;\n"
    "\n"
    "    // Smooth rainbow glow overlay (like sky effect)\n"
    "    float r = 0.5 + 0.5 * sin(6.2831 * t + 0.0);\n"
    "    float g = 0.5 + 0.5 * sin(6.2831 * t + 2.0944);\n"
    "    float b = 0.5 + 0.5 * sin(6.2831 * t + 4.1888);\n"
    "    \n"
    "    vec3 rainbowGlow = vec3(r, g, b);\n"
    "\n"
    "    // Blend with black base (dark + glow)\n"
    "    vec3 finalColor = rainbowGlow * 0.6; // Reduce brightness for sky-like soft glow\n"
    "\n"
    "    fragColor = vec4(finalColor, 1.0);\n"
    "}\n");
	
	
	
	
	
	  const char *newMaskTkkkk =
        ( "#version 310 es\n"
        "\n"
        "precision mediump float;\n"
        "\n"
        "out vec4 fragColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "discard; //\n"
        "}\n");
		
		const char *red =
    ( "#version 310 es\n"
    "\n"
    "precision mediump float;\n"        
    "\n"
    "precision highp float;\n"        
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "vec3 blackColor = vec3(1.0, 0.0, 0.0); // Changed to black\n" //Changed to Black
    "fragColor = vec4(blackColor, 1.0);\n"
    "}\n");
	
	
	
	
	
	
	
