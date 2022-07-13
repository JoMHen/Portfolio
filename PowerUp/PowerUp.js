// John Hendrick
// CS 423
// Assignment02-v2
// This program will consider a virtual art gallery
// with a center piece allowing for 4 different viewpoints
// to be selected by the user.

function init () {
	var count = 0;
	
	var stats = initStats();

    // create a scene, that will hold all our elements such as objects, cameras and lights.
    var scene = new THREE.Scene();

    // create a camera, which defines where we're looking at.
    var camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
	camera.position.x = 0;
    camera.position.y = 35;
    camera.position.z = 100;
	camera.lookAt(scene.position);
	var x = 10 + (100 * (Math.sin(-0.6)));
	camera.lookAt(new THREE.Vector3(0, 0, x));
	
    // create a render and set the size
    var renderer = new THREE.WebGLRenderer();

    renderer.setClearColor(new THREE.Color(0xEEEEEE, 1.0));
    renderer.setSize(window.innerWidth, window.innerHeight);
	renderer.shadowMap.enabled = true;
    // create the ground plane

	var loader = new THREE.GLTFLoader();
	var link = "./assets/assets/models/BottmPce.glb";
	var bottom;
	loader.load(link, (gltf) =>
	{		
		bottom = gltf.scene;
		bottom.visibility = true;
		bottom.position.x = 0;
		bottom.position.y = 27;
		bottom.position.z = 0;
		bottom.scale.x = 2;
		bottom.scale.y = 2;
		bottom.scale.z = 2;
		scene.add(bottom);
		render();
	});
	
	var top;
	link = "./assets/assets/models/TopPce.glb";
	loader.load(link, (gltf) =>
	{		
		top = gltf.scene;
		top.visibility = true;
		top.position.x = 0;
		top.position.y = 31;
		top.position.z = 0;
		top.scale.x = 2;
		top.scale.y = 2;
		top.scale.z = 2;
		scene.add(top);
		render();
	});
	
	var SecPan;
	link = "./assets/assets/models/SecurityPanel.glb";
	loader.load(link, (gltf) =>
	{		
		SecPan = gltf.scene;
		SecPan.visibility = true;
		SecPan.position.x = 0;
		SecPan.position.y = 10;
		SecPan.position.z = 0;
		SecPan.scale.x = 10;
		SecPan.scale.y = 10;
		SecPan.scale.z = 10;
		scene.add(SecPan);
	});
	
	var Crates;
	link = "./assets/assets/models/Crates.glb";
	loader.load(link, (gltf) =>
	{		
		Crates = gltf.scene;
		Crates.visibility = true;
		Crates.position.x = -60;
		Crates.position.y = 10;
		Crates.position.z = -40;
		Crates.scale.x = 10;
		Crates.scale.y = 10;
		Crates.scale.z = 10;
		scene.add(Crates);
	});
	
	
	var texture = new THREE.TextureLoader().load("./assets/assets/textures/lab_floor_texture.jpg");
    var planeGeometry = new THREE.PlaneGeometry(200, 200, 1, 1);
    var planeMaterial = new THREE.MeshPhongMaterial({map: texture});
    var plane = new THREE.Mesh(planeGeometry, planeMaterial);	

    // rotate and position the plane
    plane.rotation.x = -0.5 * Math.PI;
    plane.position.x = 0;
    plane.position.y = 0;
    plane.position.z = 0;
	plane.receiveShadow = true;
	scene.add(plane);

	var ceil = new THREE.Mesh(planeGeometry, planeMaterial);

    ceil.rotation.x = 0.5 * Math.PI;
    ceil.position.x = 0;
    ceil.position.y = 100;
    ceil.position.z = 0;
	ceil.receiveShadow = true;
	scene.add(ceil);

	texture = new THREE.TextureLoader().load("./assets/assets/textures/dark_lab_2.jpg");
	var frontGeometry = new THREE.PlaneGeometry(100, 200);
    var frontMaterial = new THREE.MeshLambertMaterial({map: texture});
    var planeFront = new THREE.Mesh(frontGeometry, frontMaterial);


    // rotate and position the plane
    planeFront.rotation.y = -1 * Math.PI;
	planeFront.position.x = 0;
    planeFront.position.y = 50;
    planeFront.position.z = 100;
    // add the plane to the scene
    scene.add(planeFront);
	
    // create the ground plane
    var backGeometry = new THREE.PlaneGeometry(200, 100);
    var backMaterial = new THREE.MeshPhongMaterial({map: texture});
    var planeBack = new THREE.Mesh(backGeometry, backMaterial);

    // rotate and position the plane
    planeBack.position.x = 0;
    planeBack.position.y = 50;
    planeBack.position.z = -100;
    // add the plane to the scene
    scene.add(planeBack);
	texture = new THREE.TextureLoader().load("./assets/assets/textures/dark lab stock.jpg");
	var leftGeometry = new THREE.PlaneGeometry(200, 100);
    var leftMaterial = new THREE.MeshLambertMaterial({map: texture});
    var planeLeft = new THREE.Mesh(leftGeometry, leftMaterial);


    // rotate and position the plane
    planeLeft.rotation.y = -0.5 * Math.PI;
	planeLeft.position.x = 100;
    planeLeft.position.y = 50;
    planeLeft.position.z = 0;
    // add the plane to the scene
    scene.add(planeLeft);
	
    var rightGeometry = new THREE.PlaneGeometry(200, 100);
    var rightMaterial = new THREE.MeshLambertMaterial({map: texture});
    var planeRight = new THREE.Mesh(rightGeometry, rightMaterial);


    // rotate and position the plane
    planeRight.rotation.y = 0.5 * Math.PI;
    planeRight.position.x = -100;
    planeRight.position.y = 50;
    planeRight.position.z = 0;
    // add the plane to the scene
    scene.add(planeRight);



    // rotate and position the plane

	//Adding a spotlight
	var spotLight = new THREE.SpotLight(0xcccccc);
	spotLight.position.set(0,35,0);
	spotLight.penumbra = 1;
	spotLight.distance = 50;
	scene.add(spotLight);
	
	var spotLight2 = new THREE.SpotLight(0xcccccc);
	spotLight2.position.set(0,-1,0);
	spotLight2.penumbra = 1;
	scene.add(spotLight2);
	
	var particleLight = new THREE.PointLight(0x444488);
	particleLight.position.set(0, 28, 0);
	particleLight.distance = 100;
	particleLight.castShadow = true;
	scene.add(particleLight);
	
	var compLight = new THREE.PointLight(0x007700);
	compLight.position.set(-15, 20, 15);
	compLight.distance = 50;
	scene.add(compLight);
	
	var compLight2 = new THREE.PointLight(0x007700);
	compLight2.position.set(20, 20, -60);
	compLight2.distance = 50;
	scene.add(compLight2);
	
	var sphereGeo = new THREE.SphereGeometry(1.1, 5,5);
	var sphere2Geo = new THREE.SphereGeometry(1.15, 5, 5);
	texture = new THREE.TextureLoader().load("./assets/assets/textures/starry-deep-outer-space-galaxy.jpg");
	var sphereMaterial = new THREE.MeshPhongMaterial({color: 0x111155, transparent: false, opacity: 0.9, emissive: 0xccffff}) 
		
	var phaazeParticle = new THREE.Mesh(sphereGeo, sphereMaterial);
	phaazeParticle.emissive = true;
	phaazeParticle.position.set(0, 28, 0);
	phaazeParticle.side = THREE.DoubleSide;
	scene.add(phaazeParticle);

	sphereMaterial = new THREE.MeshPhongMaterial({map: texture, transparent: false, opacity: 0.9, emissive: 0x004444}) 
	var phaazeShell = new THREE.Mesh(sphere2Geo, sphereMaterial);
	phaazeShell.position.set(0, 28, 0);
	phaazeShell.material.color.setHex(0xccffff);
	scene.add(phaazeShell);
	
	var ShieldGeo = new THREE.CylinderGeometry(8, 8, 40);
	ShieldMaterial = new THREE.MeshPhongMaterial({color: 0x004444, transparent: true, opacity: 0.3}) 
	var  Shield = new THREE.Mesh(ShieldGeo, ShieldMaterial);
	Shield.position.set(0, 35, 0);
	Shield.material.color.setHex(0xccffff);
	scene.add(Shield);


    // add subtle ambient lighting
    var ambientLight = new THREE.AmbientLight(0x555599);
    scene.add(ambientLight);
	
	var onff = true;
	var controls = new function () {
		this.Current = "Front";
		this.Status = "ON";
		this.Entrance = function () {
			camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
			camera.position.x = planeFront.position.x;
			camera.position.y = 35;
			camera.position.z = planeFront.position.z;
			camera.lookAt(new THREE.Vector3(0, 0, x));
			this.Current = "Entrance";
		}
		
		this.SecurityPanel = function () {
			camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
			camera.position.x = 0;
			camera.position.y = 35;
			camera.position.z = 50;
			camera.lookAt(new THREE.Vector3(0,0, x * 2));
			this.Current = "SecurityPanel";
		}
		this.CloseUp = function () {
			camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
			camera.position.x = 10;
			camera.position.y = 25;
			camera.position.z = 15;
			camera.lookAt(new THREE.Vector3(x, -x, x * 2.5));
			this.Current = "CloseUp";
		}
		this.ShieldONOFF = function () {
			if (onff === true)
				{onff = false;
				this.Status = "OFF";}
			else if (onff === false)
				{onff = true;
				this.Status = "ON";}
		}
	}
	var gui = new dat.GUI();
	
	gui.add(controls, 'Entrance');
	gui.add(controls, 'SecurityPanel');
	gui.add(controls, 'CloseUp');
	gui.add(controls, 'Current').listen();
	gui.add(controls, 'ShieldONOFF');
	gui.add(controls, 'Status').listen();
	

    // add the output of the renderer to the html element
    document.getElementById("WebGL-output").appendChild(renderer.domElement);
	
	function moveShield () {
		if (onff === true)
			{if (Shield.position.y > 35)
				{Shield.position.y -= 0.1;}
			}
		if (onff === false)
			{if (Shield.position.y < 100)
				{Shield.position.y += 0.1;}
			}
	}
	
   function render() {

        stats.update();
        // render using requestAnimationFrame
        requestAnimationFrame(render);
        renderer.render(scene, camera);
		
		// Acceleration
		if (count < 200) {
			bottom.position.y += 0.000045 * count;
			bottom.rotation.y += (count / 4000) * Math.PI;
			top.position.y -= 0.000045 *  count;
			top.rotation.y -= (count / 4000) * Math.PI;
			if (count % 20 === 0) {
			particleLight.intensity += (count / 200);
			phaazeParticle.material.emissive.set(count * 16);
			phaazeShell.material.emissive.set(count * 16);
			}
			else if (count % 5 === 0) {
			particleLight.intensity = (count / 200);
			phaazeParticle.material.emissive.setHex(0xccffff);
			phaazeShell.material.emissive.setHex(0x004444);}
			
			phaazeParticle.rotation.x += (count / 4000) * Math.PI;
			phaazeParticle.rotation.z -= (count / 4000) * Math.PI;
			phaazeShell.rotation.y += (count / 4000) * Math.PI;
			phaazeShell.rotation.x -= (count / 4000) * Math.PI;
		}	// Deceleration
		if (count > 200 && count < 400) {
			bottom.position.y -= 0.000045 * (400 - count);
			bottom.rotation.y -= ((400 - count) / 4000) * Math.PI;
			top.position.y += 0.000045 * (400 - count);
			top.rotation.y += ((400 - count) / 4000) * Math.PI;
			if (count % 20 === 0) {
			particleLight.intensity -= ((400 - count) / 200);
			phaazeParticle.material.emissive.set((400 - count) * 16);
			phaazeShell.material.emissive.set((400 - count) * 16);
			}
			else if (count % 5 === 0){
			particleLight.intensity = ((400 - count) / 200);
			phaazeParticle.material.emissive.setHex(0xccffff);
			phaazeShell.material.emissive.setHex(0x004444);}
			
			phaazeParticle.rotation.x -= ((400 - count) / 4000) * Math.PI;
			phaazeParticle.rotation.z += ((400 - count) / 4000) * Math.PI;
			phaazeShell.rotation.y -= ((400 - count) / 4000) * Math.PI;
			phaazeShell.rotation.x += ((400 - count) / 4000) * Math.PI;
		}
		if (count === 400)
		{count = 0;}
	
		moveShield();
		count++;
    }

	render();
	
    function initStats() {

        var stats = new Stats();

        stats.setMode(0); // 0: fps, 1: ms

        // Align top-left
        stats.domElement.style.position = 'absolute';
        stats.domElement.style.left = '0px';
        stats.domElement.style.top = '0px';

        document.getElementById("Stats-output").appendChild(stats.domElement);

        return stats;
    }
	
}

window.onload = init;