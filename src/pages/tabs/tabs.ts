import { Component } from '@angular/core';

import { PartiesPage } from '../parties/parties';
import { ConstituenciesPage } from '../constituencies/constituencies';
import { CouncilsPage } from '../councils/councils';

@Component({
  templateUrl: 'tabs.html'
})
export class TabsPage {
  // this tells the tabs component which Pages
  // should be each tab's root Page
  tabPartiesRoot: any = PartiesPage;
  tabConstituenciesRoot: any = ConstituenciesPage;
  tabCouncilsRoot: any = CouncilsPage;

  constructor() {

  }
}
