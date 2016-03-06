void scenario::addBody(body* p_nb) {
  bodies.push_back(p_nb); // Add pointer to dynamic array
}

void scenario::delBody(int p_bdID) {
  delete(bodies[p_bdID]); // Free memory associated with pointer
  bodies.erase(bodies.begin()+p_bdID); // Erase pointer from vector
}

void scenario::deleteAllBodies() {
  for(int i = 0; i < bodies.size(); i++) {
    delete(bodies.[i]); // Free all memory in vector
  }
  bodies.clear(); // Reset vector
}
