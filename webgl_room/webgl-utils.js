(function (global) {
  "use strict";

  function createProgram(gl, vertexShaderSource, fragmentShaderSource) {
    const vertexShader = compileShader(
      gl,
      gl.VERTEX_SHADER,
      vertexShaderSource
    );
    const fragmentShader = compileShader(
      gl,
      gl.FRAGMENT_SHADER,
      fragmentShaderSource
    );
    const program = gl.createProgram();
    gl.attachShader(program, vertexShader);
    gl.attachShader(program, fragmentShader);
    gl.linkProgram(program);

    if (!gl.getProgramParameter(program, gl.LINK_STATUS)) {
      console.error("Could not link shaders: ", gl.getProgramInfoLog(program));
      gl.deleteProgram(program);
      return null;
    }

    return program;
  }

  function compileShader(gl, shaderType, shaderSource) {
    const shader = gl.createShader(shaderType);
    gl.shaderSource(shader, shaderSource);
    gl.compileShader(shader);

    if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
      console.error("Could not compile shader: ", gl.getShaderInfoLog(shader));
      gl.deleteShader(shader);
      return null;
    }

    return shader;
  }

  global.webglUtils = {
    createProgram: createProgram,
    compileShader: compileShader,
  };
})(this);
