import { Injectable } from '@angular/core';
import { Router } from 'express';

@Injectable({
  providedIn: 'root',
})
export class MySymbolsService {
  selectedSymbols: any[] = [];

  constructor() {
    this.loadSelectedSymbols();
  }

  saveSelectedSymbols() {
    localStorage.setItem(
      'selectedSymbols',
      JSON.stringify(this.selectedSymbols)
    );
  }

  loadSelectedSymbols() {
    const savedSymbols = localStorage.getItem('selectedSymbols');
    if (savedSymbols) {
      this.selectedSymbols = JSON.parse(savedSymbols);
    }
  }

  removeSelectedSymbol(selectedSymbol: any) {
    const index = this.selectedSymbols.indexOf(selectedSymbol);
    if (index !== -1) {
      this.selectedSymbols.splice(index, 1);
    }

    this.saveSelectedSymbols();
  }
}
