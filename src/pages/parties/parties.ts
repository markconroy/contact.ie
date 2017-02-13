import { Component } from '@angular/core';
import { Http } from '@angular/http';
import 'rxjs/add/operator/map';
import { NavController, NavParams } from 'ionic-angular';

/*
  Generated class for the Parties page.

  See http://ionicframework.com/docs/v2/components/#navigation for more info on
  Ionic pages and navigation.
*/
@Component({
  selector: 'page-parties',
  templateUrl: 'parties.html'
})
export class PartiesPage {

  parties: any;

  constructor(public navCtrl: NavController, public navParams: NavParams, public http: Http) {
    this.http.get('./assets/emails/parties.json').map(res => res.json()).subscribe(
      data => {
        this.parties = data;
      },
      err => {
        console.log("Error! We couldn't retrieve the parties list.");
      }
    );
  }

  ionViewDidLoad() {
    console.log('ionViewDidLoad PartiesPage');
  }

}
