import { Routes } from '@angular/router';
import { DashboardComponent } from './dashboard/dashboard.component';
import { SymbolsComponent } from './symbols/symbols.component';

export const routes: Routes = [
  { path: '', component: DashboardComponent },
  { path: 'stocks', component: SymbolsComponent },
  { path: 'forex_pairs', component: SymbolsComponent },
  { path: 'cryptocurrencies', component: SymbolsComponent },
  { path: 'etf', component: SymbolsComponent },
  { path: 'indices', component: SymbolsComponent },
  { path: '**', redirectTo: '/', pathMatch: 'full' },
];
