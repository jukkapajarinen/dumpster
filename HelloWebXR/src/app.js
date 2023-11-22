import * as THREE from 'three';
import { ARButton } from 'three/examples/jsm/webxr/ARButton.js';
import { createText } from 'three/examples/jsm/webxr/Text2D.js';

let camera, scene, renderer, controller;

const init = () => {
  const container = document.createElement( 'div' );
  document.body.appendChild( container );
  scene = new THREE.Scene();
  camera = new THREE.PerspectiveCamera( 70, window.innerWidth / window.innerHeight, 0.01, 20 );
  const light = new THREE.HemisphereLight( 0xffffff, 0xbbbbff, 1 );
  light.position.set( 0.5, 1, 0.25 );
  scene.add( light );
  renderer = new THREE.WebGLRenderer( { antialias: true, alpha: true } );
  renderer.setPixelRatio( window.devicePixelRatio );
  renderer.setSize( window.innerWidth, window.innerHeight );
  renderer.xr.enabled = true;
  container.appendChild( renderer.domElement );
  document.body.appendChild( ARButton.createButton( renderer ) );
  controller = renderer.xr.getController( 0 );
  controller.addEventListener( 'select', () => {
    const text = createText(["Jukka", "Kati", "Aapo"][Math.floor((Math.random() * 3))], 0.1 );
    text.position.set( 0, 0, 0).applyMatrix4( controller.matrixWorld );
    text.quaternion.setFromRotationMatrix( controller.matrixWorld );
    scene.add( text );
  } );
  scene.add( controller );
  window.addEventListener( 'resize', onWindowResize );
}

const animate = () => {
  renderer.setAnimationLoop(() => renderer.render( scene, camera ));
}

const onWindowResize = () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize( window.innerWidth, window.innerHeight );
}

init();
animate();