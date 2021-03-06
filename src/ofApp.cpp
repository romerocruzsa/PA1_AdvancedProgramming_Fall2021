#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 

	resetParticles();

	sound.load("rickroll.mp3");
	sound.setVolume(0.5);
}

//--------------------------------------------------------------
void ofApp::resetParticles(){

	//these are the attraction points used in the fourth demo 
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( glm::vec3( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) , 0) );
	}
	
	attractPointsWithMovement = attractPoints;
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
	}	
}

//--------------------------------------------------------------
void ofApp::update(){
	if(currentMode == PARTICLE_MODE_PAUSE){
		return;
	}
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);
		p[i].update();
	}
	if(replay==true){
		if(counter==0){
			reverse(keys.begin(),keys.end());
			pressedKeys=keys.end();
			keyPressed(*pressedKeys);
			keys.pop_back();
			counter=60;
			reverse(keys.begin(), keys.end());
		}
		else{
			counter--;
		}
	}
	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}	
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(38,191,202), ofColor(24,37,69));

	for(unsigned int i = 0; i < p.size(); i++){
		p[i].draw();
	}

	ofSetColor(190);
	if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
		for(unsigned int i = 0; i < attractPoints.size(); i++){
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	if(currentMode == PARTICLE_MODE_PARTYTIME){
		ofBackgroundGradient(ofColor(rand() % 255,rand() % 255,rand() % 255), ofColor(rand() % 255,rand() % 255,rand() % 255));
	}

	ofSetColor(230);	
	ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode. \nPress A to pause. \nPress I to increase size. \nPress D to decrease size. \nPress F to speed up particles.\nPress S to slow down particles. \nPress T for Party Time (warning: flashing lights!)", 10, 20);
		
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(replay == true){
		if(keys.size() == 0 || (key == 'c')){
			resetParticles();
			replay = false;
		}
		else if(key !=* pressedKeys){
			return;
		}
		key =* pressedKeys;
	}
	if( key == '1'){
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";			
	}
	if( key == '2'){
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse"; 				
	}
	if( key == '3'){
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:"; 						
	}
	if( key == '4'){
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation"; 						
		resetParticles();
		sound.stop();
	}
	// pauseParticle function implemented. When key "A" is pressed, particles will stop moving with respect to 
	// the last mode that was enabled.	
	if(key == 'a'){
		currentMode = PARTICLE_MODE_PAUSE;
		// currentModeStr = "A - PARTICLE_MODE_PAUSE: particles are suspended in the air";
	}		
	if(key == 'i'){			//triples the size of all particles
		for(unsigned int i = 0; i < p.size(); i++){
		p[i].scale *= 3.0;
		}
	}
	if(key == 'd'){			//thirds the size of all particles
		for(unsigned int i = 0; i < p.size(); i++){
		p[i].scale *= 1.0/3.0;
		}
	}
	if(key == 'f'){
		for(unsigned int i = 0; i<p.size(); i++){
			p[i].vel.x *= 4.0;
			p[i].vel.y *= 4.0;
			}		
	}
	if(key == 's'){
		for(unsigned int i = 0; i<p.size(); i++){
			p[i].vel.x *= 0.25;
			p[i].vel.y *= 0.25;		
			}
	}
	if(key == 'r'){
		currentModeStr = "R - RECORD: Recording is in session";
		record=!record;
	}
	if(key == 'p'){
		currentModeStr = "P - REPLAY: Recording is being played";
		replay=true;
	}
	if(record == true){
		keys.push_back(key);
	}
	if( key == ' ' ){
		resetParticles();
	}

	if(key == 't'){
		currentMode = PARTICLE_MODE_PARTYTIME;
		currentModeStr = "T - PARTICLE_MODE_PARTYTIME: ;)";
		sound.play();
	}

	if(key != 't'){
		sound.stop();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
