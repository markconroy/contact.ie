import { Component } from '@angular/core';

import { HomePage } from '../home/home';
import { AboutPage } from '../about/about';
import { ContactPage } from '../contact/contact';
import { HelpusPage } from '../helpus/helpus';
import { PartiesPage } from '../parties/parties';
import { ConstituenciesPage } from '../constituencies/constituencies';

@Component({
  templateUrl: 'tabs.html'
})
export class TabsPage {
  // this tells the tabs component which Pages
  // should be each tab's root Page
  tab1Root: any = HomePage;
  tab2Root: any = PartiesPage;
  tab3Root: any = ConstituenciesPage;
  tab4Root: any = HelpusPage;
  tab5Root: any = ContactPage;

  constructor() {

  }
}
