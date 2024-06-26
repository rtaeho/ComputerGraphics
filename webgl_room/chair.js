const canvas = document.getElementById("glcanvas");
const gl =
  canvas.getContext("webgl") || canvas.getContext("experimental-webgl");

// Load shaders
const vsSource = `
    attribute vec4 aVertexPosition;
    attribute vec2 aTextureCoord;
    uniform mat4 uModelViewMatrix;
    uniform mat4 uProjectionMatrix;
    varying highp vec2 vTextureCoord;
    void main(void) {
        gl_Position = uProjectionMatrix * uModelViewMatrix * aVertexPosition;
        vTextureCoord = aTextureCoord;
    }
`;

const fsSource = `
    precision mediump float;
    varying highp vec2 vTextureCoord;
    uniform sampler2D uSampler;
    uniform vec3 uLightDirection;
    uniform vec4 uLightColor;
    void main(void) {
        vec4 texelColor = texture2D(uSampler, vTextureCoord);
        vec3 lightDir = normalize(uLightDirection);
        float lightIntensity = max(dot(lightDir, vec3(0, 0, 1)), 0.0);
        gl_FragColor = texelColor * vec4(vec3(lightIntensity) * uLightColor.rgb, uLightColor.a);
    }
`;

const shaderProgram = initShaderProgram(gl, vsSource, fsSource);
const programInfo = {
  program: shaderProgram,
  attribLocations: {
    vertexPosition: gl.getAttribLocation(shaderProgram, "aVertexPosition"),
    textureCoord: gl.getAttribLocation(shaderProgram, "aTextureCoord"),
  },
  uniformLocations: {
    projectionMatrix: gl.getUniformLocation(shaderProgram, "uProjectionMatrix"),
    modelViewMatrix: gl.getUniformLocation(shaderProgram, "uModelViewMatrix"),
    uSampler: gl.getUniformLocation(shaderProgram, "uSampler"),
    lightDirection: gl.getUniformLocation(shaderProgram, "uLightDirection"),
    lightColor: gl.getUniformLocation(shaderProgram, "uLightColor"),
  },
};

// Define the chair vertices and texture coordinates
const chairVertices = [
  // Seat (Top)
  -1.5, 0.0, 1.5, 1.5, 0.0, 1.5, 1.5, 0.0, -1.5, -1.5, 0.0, -1.5,
  // Seat (Bottom)
  -1.5, -0.1, 1.5, 1.5, -0.1, 1.5, 1.5, -0.1, -1.5, -1.5, -0.1, -1.5,
  // Seat Sides
  -1.5, 0.0, 1.5, -1.5, -0.1, 1.5, 1.5, -0.1, 1.5, 1.5, 0.0, 1.5, -1.5, 0.0,
  -1.5, -1.5, -0.1, -1.5, 1.5, -0.1, -1.5, 1.5, 0.0, -1.5, -1.5, 0.0, 1.5, -1.5,
  -0.1, 1.5, -1.5, -0.1, -1.5, -1.5, 0.0, -1.5, 1.5, 0.0, 1.5, 1.5, -0.1, 1.5,
  1.5, -0.1, -1.5, 1.5, 0.0, -1.5,

  // Back (Front)
  -1.5, 1.6, -1.4, 1.5, 1.6, -1.4, 1.5, 0.0, -1.4, -1.5, 0.0, -1.4,
  // Back (Back)
  -1.5, 1.6, -1.5, 1.5, 1.6, -1.5, 1.5, 0.0, -1.5, -1.5, 0.0, -1.5,
  // Back Sides
  -1.5, 1.6, -1.4, -1.5, 1.6, -1.5, 1.5, 1.6, -1.5, 1.5, 1.6, -1.4, -1.5, 0.0,
  -1.4, -1.5, 0.0, -1.5, 1.5, 0.0, -1.5, 1.5, 0.0, -1.4,

  // Legs
  // Back right leg
  1.4, -0.1, -1.4, 1.4, -2.0, -1.4, 1.6, -2.0, -1.4, 1.6, -0.1, -1.4, 1.4, -0.1,
  -1.6, 1.4, -2.0, -1.6, 1.6, -2.0, -1.6, 1.6, -0.1, -1.6, 1.4, -0.1, -1.4, 1.4,
  -2.0, -1.4, 1.4, -2.0, -1.6, 1.4, -0.1, -1.6, 1.6, -0.1, -1.4, 1.6, -2.0,
  -1.4, 1.6, -2.0, -1.6, 1.6, -0.1, -1.6,

  // Back left leg
  -1.4, -0.1, -1.4, -1.4, -2.0, -1.4, -1.6, -2.0, -1.4, -1.6, -0.1, -1.4, -1.4,
  -0.1, -1.6, -1.4, -2.0, -1.6, -1.6, -2.0, -1.6, -1.6, -0.1, -1.6, -1.4, -0.1,
  -1.4, -1.4, -2.0, -1.4, -1.4, -2.0, -1.6, -1.4, -0.1, -1.6, -1.6, -0.1, -1.4,
  -1.6, -2.0, -1.4, -1.6, -2.0, -1.6, -1.6, -0.1, -1.6,

  // Front right leg
  1.4, -0.1, 1.4, 1.4, -2.0, 1.4, 1.6, -2.0, 1.4, 1.6, -0.1, 1.4, 1.4, -0.1,
  1.6, 1.4, -2.0, 1.6, 1.6, -2.0, 1.6, 1.6, -0.1, 1.6, 1.4, -0.1, 1.4, 1.4,
  -2.0, 1.4, 1.4, -2.0, 1.6, 1.4, -0.1, 1.6, 1.6, -0.1, 1.4, 1.6, -2.0, 1.4,
  1.6, -2.0, 1.6, 1.6, -0.1, 1.6,

  // Front left leg
  -1.4, -0.1, 1.4, -1.4, -2.0, 1.4, -1.6, -2.0, 1.4, -1.6, -0.1, 1.4, -1.4,
  -0.1, 1.6, -1.4, -2.0, 1.6, -1.6, -2.0, 1.6, -1.6, -0.1, 1.6, -1.4, -0.1, 1.4,
  -1.4, -2.0, 1.4, -1.4, -2.0, 1.6, -1.4, -0.1, 1.6, -1.6, -0.1, 1.4, -1.6,
  -2.0, 1.4, -1.6, -2.0, 1.6, -1.6, -0.1, 1.6,
];

const chairTextureCoordinates = [
  // Seat
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  1.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  1.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  1.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  1.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  1.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  1.0, // Back
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  1.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  1.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  1.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  1.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  1.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  1.0,

  // Legs
  // Back right leg
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,

  // Back left leg
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,

  // Front right leg
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,

  // Front left leg
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  0.0,
  1.0,
  1.0,
  0.0,
  0.0,
  0.0,
  0.0,
  1.0,
  1.0,
  1.0,
  1.0,
  0.0,
];

const chairIndices = [
  // Seat
  0,
  1,
  2,
  0,
  2,
  3,
  4,
  5,
  6,
  4,
  6,
  7,
  8,
  9,
  10,
  8,
  10,
  11,
  12,
  13,
  14,
  12,
  14,
  15,
  16,
  17,
  18,
  16,
  18,
  19,
  20,
  21,
  22,
  20,
  22,
  23, // Back
  24,
  25,
  26,
  24,
  26,
  27,
  28,
  29,
  30,
  28,
  30,
  31,
  32,
  33,
  34,
  32,
  34,
  35,
  36,
  37,
  38,
  36,
  38,
  39,
  40,
  41,
  42,
  40,
  42,
  43,
  44,
  45,
  46,
  44,
  46,
  47,

  // Legs
  // Back right leg
  48,
  49,
  50,
  48,
  50,
  51,
  52,
  53,
  54,
  52,
  54,
  55,
  56,
  57,
  58,
  56,
  58,
  59,
  60,
  61,
  62,
  60,
  62,
  63,
  // Back left leg
  64,
  65,
  66,
  64,
  66,
  67,
  68,
  69,
  70,
  68,
  70,
  71,
  72,
  73,
  74,
  72,
  74,
  75,
  76,
  77,
  78,
  76,
  78,
  79,
  // Front right leg
  80,
  81,
  82,
  80,
  82,
  83,
  84,
  85,
  86,
  84,
  86,
  87,
  88,
  89,
  90,
  88,
  90,
  91,
  92,
  93,
  94,
  92,
  94,
  95,
  // Front left leg
  96,
  97,
  98,
  96,
  98,
  99,
  100,
  101,
  102,
  100,
  102,
  103,
  104,
  105,
  106,
  104,
  106,
  107,
  108,
  109,
  110,
  108,
  110,
  111,
];

const buffers = initBuffers(
  gl,
  chairVertices,
  chairTextureCoordinates,
  chairIndices
);

let texturesLoaded = 0;
const textures = {
  texture1: loadTexture(gl, "textures/texture1.jpg", onTextureLoad),
  texture2: loadTexture(gl, "textures/texture2.jpg", onTextureLoad),
  texture3: loadTexture(gl, "textures/texture3.jpg", onTextureLoad),
};

let rotationAngle = 0;

document.getElementById("rotateClockwise").addEventListener("click", () => {
  rotationAngle += 5;
  drawScene();
});

document
  .getElementById("rotateCounterClockwise")
  .addEventListener("click", () => {
    rotationAngle -= 5;
    drawScene();
  });

function onTextureLoad() {
  texturesLoaded++;
  if (texturesLoaded === 3) {
    drawScene();
  }
}

function initShaderProgram(gl, vsSource, fsSource) {
  const vertexShader = loadShader(gl, gl.VERTEX_SHADER, vsSource);
  const fragmentShader = loadShader(gl, gl.FRAGMENT_SHADER, fsSource);
  const shaderProgram = gl.createProgram();
  gl.attachShader(shaderProgram, vertexShader);
  gl.attachShader(shaderProgram, fragmentShader);
  gl.linkProgram(shaderProgram);

  if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
    alert(
      "Unable to initialize the shader program: " +
        gl.getProgramInfoLog(shaderProgram)
    );
    return null;
  }

  return shaderProgram;
}

function loadShader(gl, type, source) {
  const shader = gl.createShader(type);
  gl.shaderSource(shader, source);
  gl.compileShader(shader);
  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    alert(
      "An error occurred compiling the shaders: " + gl.getShaderInfoLog(shader)
    );
    gl.deleteShader(shader);
    return null;
  }

  return shader;
}

function initBuffers(gl, vertices, textureCoordinates, indices) {
  const vertexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
  const textureCoordBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, textureCoordBuffer);
  gl.bufferData(
    gl.ARRAY_BUFFER,
    new Float32Array(textureCoordinates),
    gl.STATIC_DRAW
  );

  const indexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, indexBuffer);
  gl.bufferData(
    gl.ELEMENT_ARRAY_BUFFER,
    new Uint16Array(indices),
    gl.STATIC_DRAW
  );

  return {
    position: vertexBuffer,
    textureCoord: textureCoordBuffer,
    indices: indexBuffer,
  };
}

function loadTexture(gl, url, onLoadCallback) {
  const texture = gl.createTexture();
  gl.bindTexture(gl.TEXTURE_2D, texture);
  const level = 0;
  const internalFormat = gl.RGBA;
  const width = 1;
  const height = 1;
  const border = 0;
  const srcFormat = gl.RGBA;
  const srcType = gl.UNSIGNED_BYTE;
  const pixel = new Uint8Array([0, 0, 255, 255]);
  gl.texImage2D(
    gl.TEXTURE_2D,
    level,
    internalFormat,
    width,
    height,
    border,
    srcFormat,
    srcType,
    pixel
  );

  const image = new Image();
  image.onload = function () {
    gl.bindTexture(gl.TEXTURE_2D, texture);
    gl.texImage2D(
      gl.TEXTURE_2D,
      level,
      internalFormat,
      srcFormat,
      srcType,
      image
    );

    if (isPowerOf2(image.width) && isPowerOf2(image.height)) {
      gl.generateMipmap(gl.TEXTURE_2D);
    } else {
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    }

    if (onLoadCallback) {
      onLoadCallback();
    }
  };
  image.src = url;

  return texture;
}

function isPowerOf2(value) {
  return (value & (value - 1)) === 0;
}

function drawScene() {
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  gl.useProgram(programInfo.program);
  const projectionMatrix = mat4.create();
  mat4.perspective(
    projectionMatrix,
    (45 * Math.PI) / 180,
    gl.canvas.clientWidth / gl.canvas.clientHeight,
    0.1,
    100.0
  );

  const modelViewMatrix = mat4.create();
  mat4.translate(modelViewMatrix, modelViewMatrix, [-0.0, 0.0, -6.0]);
  mat4.rotate(
    modelViewMatrix,
    modelViewMatrix,
    (rotationAngle * Math.PI) / 180,
    [0, 1, 0]
  );

  {
    const numComponents = 3;
    const type = gl.FLOAT;
    const normalize = false;
    const stride = 0;
    const offset = 0;
    gl.bindBuffer(gl.ARRAY_BUFFER, buffers.position);
    gl.vertexAttribPointer(
      programInfo.attribLocations.vertexPosition,
      numComponents,
      type,
      normalize,
      stride,
      offset
    );
    gl.enableVertexAttribArray(programInfo.attribLocations.vertexPosition);
  }

  {
    const numComponents = 2;
    const type = gl.FLOAT;
    const normalize = false;
    const stride = 0;
    const offset = 0;
    gl.bindBuffer(gl.ARRAY_BUFFER, buffers.textureCoord);
    gl.vertexAttribPointer(
      programInfo.attribLocations.textureCoord,
      numComponents,
      type,
      normalize,
      stride,
      offset
    );
    gl.enableVertexAttribArray(programInfo.attribLocations.textureCoord);
  }

  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, buffers.indices);

  gl.useProgram(programInfo.program);
  gl.uniformMatrix4fv(
    programInfo.uniformLocations.projectionMatrix,
    false,
    projectionMatrix
  );
  gl.uniformMatrix4fv(
    programInfo.uniformLocations.modelViewMatrix,
    false,
    modelViewMatrix
  );

  // Set lighting uniforms
  const lightDirection = vec3.fromValues(0.0, 0.0, 1.0);
  const lightColor = vec4.fromValues(1.0, 1.0, 1.0, 1.0);
  gl.uniform3fv(programInfo.uniformLocations.lightDirection, lightDirection);
  gl.uniform4fv(programInfo.uniformLocations.lightColor, lightColor);

  drawPart(gl, 0, 24, textures.texture3); // Seat
  drawPart(gl, 24, 48, textures.texture1); // Back
  drawPart(gl, 48, 96, textures.texture2); // Legs

  drawAxes(gl, modelViewMatrix, projectionMatrix);
}

function drawPart(gl, offset, count, texture) {
  gl.activeTexture(gl.TEXTURE0);
  gl.bindTexture(gl.TEXTURE_2D, texture);
  gl.uniform1i(programInfo.uniformLocations.uSampler, 0);
  {
    const type = gl.UNSIGNED_SHORT;
    gl.drawElements(gl.TRIANGLES, count, type, offset * 2);
  }
}

function drawAxes(gl, modelViewMatrix, projectionMatrix) {
  const axesVertices = new Float32Array([
    // X axis (red)
    0.0, 0.0, 0.0, 3.0, 0.0, 0.0,
    // Y axis (green)
    0.0, 0.0, 0.0, 0.0, 3.0, 0.0,
    // Z axis (blue)
    0.0, 0.0, 0.0, 0.0, 0.0, 3.0,
  ]);
  const axesColors = new Float32Array([
    // X axis (red)
    1.0, 0.0, 0.0, 1.0, 0.0, 0.0,
    // Y axis (green)
    0.0, 1.0, 0.0, 0.0, 1.0, 0.0,
    // Z axis (blue)
    0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
  ]);

  const axisShaderProgram = initShaderProgram(
    gl,
    `
  attribute vec4 aVertexPosition;
  attribute vec4 aVertexColor;
  uniform mat4 uModelViewMatrix;
  uniform mat4 uProjectionMatrix;
  varying lowp vec4 vColor;
  void main(void) {
      gl_Position = uProjectionMatrix * uModelViewMatrix * aVertexPosition;
      vColor = aVertexColor;
  }
`,
    `
  varying lowp vec4 vColor;
  void main(void) {
      gl_FragColor = vColor;
  }
`
  );

  const axisProgramInfo = {
    program: axisShaderProgram,
    attribLocations: {
      vertexPosition: gl.getAttribLocation(
        axisShaderProgram,
        "aVertexPosition"
      ),
      vertexColor: gl.getAttribLocation(axisShaderProgram, "aVertexColor"),
    },
    uniformLocations: {
      projectionMatrix: gl.getUniformLocation(
        axisShaderProgram,
        "uProjectionMatrix"
      ),
      modelViewMatrix: gl.getUniformLocation(
        axisShaderProgram,
        "uModelViewMatrix"
      ),
    },
  };

  const axisBuffers = {
    position: gl.createBuffer(),
    color: gl.createBuffer(),
  };

  gl.bindBuffer(gl.ARRAY_BUFFER, axisBuffers.position);
  gl.bufferData(gl.ARRAY_BUFFER, axesVertices, gl.STATIC_DRAW);
  gl.bindBuffer(gl.ARRAY_BUFFER, axisBuffers.color);
  gl.bufferData(gl.ARRAY_BUFFER, axesColors, gl.STATIC_DRAW);

  gl.useProgram(axisProgramInfo.program);

  gl.bindBuffer(gl.ARRAY_BUFFER, axisBuffers.position);
  gl.vertexAttribPointer(
    axisProgramInfo.attribLocations.vertexPosition,
    3,
    gl.FLOAT,
    false,
    0,
    0
  );
  gl.enableVertexAttribArray(axisProgramInfo.attribLocations.vertexPosition);

  gl.bindBuffer(gl.ARRAY_BUFFER, axisBuffers.color);
  gl.vertexAttribPointer(
    axisProgramInfo.attribLocations.vertexColor,
    3,
    gl.FLOAT,
    false,
    0,
    0
  );
  gl.enableVertexAttribArray(axisProgramInfo.attribLocations.vertexColor);

  gl.uniformMatrix4fv(
    axisProgramInfo.uniformLocations.projectionMatrix,
    false,
    projectionMatrix
  );
  gl.uniformMatrix4fv(
    axisProgramInfo.uniformLocations.modelViewMatrix,
    false,
    modelViewMatrix
  );

  gl.drawArrays(gl.LINES, 0, 6);
}
