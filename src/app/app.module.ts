import { NgModule, ErrorHandler } from '@angular/core';
import { IonicApp, IonicModule, IonicErrorHandler } from 'ionic-angular';
import { MyApp } from './app.component';
import { AboutPage } from '../pages/about/about';
import { ContactPage } from '../pages/contact/contact';
import { HomePage } from '../pages/home/home';
import { TabsPage } from '../pages/tabs/tabs';
import { HelpusPage } from '../pages/helpus/helpus';
import { PartiesPage } from '../pages/parties/parties'
import { ConstituenciesPage } from '../pages/constituencies/constituencies'
import { CouncilsPage } from '../pages/councils/councils'

@NgModule({
  declarations: [
    MyApp,
    AboutPage,
    ContactPage,
    HomePage,
    TabsPage,
    HelpusPage,
    PartiesPage,
    ConstituenciesPage,
    CouncilsPage
  ],
  imports: [
    IonicModule.forRoot(MyApp)
  ],
  bootstrap: [IonicApp],
  entryComponents: [
    MyApp,
    AboutPage,
    ContactPage,
    HomePage,
    TabsPage,
    HelpusPage,
    PartiesPage,
    ConstituenciesPage,
    CouncilsPage
  ],
  providers: [{provide: ErrorHandler, useClass: IonicErrorHandler}]
})
export class AppModule {}
