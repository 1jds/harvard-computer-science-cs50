import { useState } from "react";
import "./index.css";
import Navbar from "./Navbar";
import Landing from "./Landing";
import classroom from "./assets/hiroyoshi-urushima-vfRkE_9wuPo-unsplash.jpg";

function App() {
  return (
    <>
      <Landing />
      {/* <Navbar /> */}
      <main className="content-grid">
        {/* <img
          // className="full-width full-cover overlayed"
          className="mobile-landing"
          src={classroom}
          alt="Japanese school room"
        /> */}
        <h1 className="overlayed">Hello World!</h1>
        {/* <p>
          Lorem ipsum dolor sit amet consectetur adipisicing elit. Repudiandae
          sapiente fugiat asperiores nisi dicta voluptates ea quasi, atque
          minima, aspernatur iste nesciunt aliquam! Iusto iure eveniet explicabo
          dicta nobis ad? Enim ducimus velit commodi voluptatem, eum animi culpa
          minus repellat totam, labore ut repudiandae incidunt modi blanditiis
          facere sunt fugiat aperiam quam deleniti eligendi tenetur illum
          aspernatur dicta nihil! A. Quibusdam, est! Debitis maxime tenetur
          ipsam, asperiores adipisci nostrum, nihil mollitia perspiciatis
          necessitatibus non at quibusdam deleniti sunt quos. Dignissimos, vel
          dolore voluptatibus cum est alias molestias iusto eos voluptatum.
        </p>
        <p className="breakout">
          Lorem ipsum dolor sit amet consectetur adipisicing elit. Repudiandae
          sapiente fugiat asperiores nisi dicta voluptates ea quasi, atque
          minima, aspernatur iste nesciunt aliquam! Iusto iure eveniet explicabo
          dicta nobis ad? Enim ducimus velit commodi voluptatem, eum animi culpa
          minus repellat totam, labore ut repudiandae incidunt modi blanditiis
          facere sunt fugiat aperiam quam deleniti eligendi tenetur illum
          aspernatur dicta nihil! A. Quibusdam, est! Debitis maxime tenetur
          ipsam, asperiores adipisci nostrum, nihil mollitia perspiciatis
          necessitatibus non at quibusdam deleniti sunt quos. Dignissimos, vel
          dolore voluptatibus cum est alias molestias iusto eos voluptatum.
        </p>
        <p>
          Lorem ipsum dolor sit amet consectetur adipisicing elit. Repudiandae
          sapiente fugiat asperiores nisi dicta voluptates ea quasi, atque
          minima, aspernatur iste nesciunt aliquam! Iusto iure eveniet explicabo
          dicta nobis ad? Enim ducimus velit commodi voluptatem, eum animi culpa
          minus repellat totam, labore ut repudiandae incidunt modi blanditiis
          facere sunt fugiat aperiam quam deleniti eligendi tenetur illum
          aspernatur dicta nihil! A. Quibusdam, est! Debitis maxime tenetur
          ipsam, asperiores adipisci nostrum, nihil mollitia perspiciatis
          necessitatibus non at quibusdam deleniti sunt quos. Dignissimos, vel
          dolore voluptatibus cum est alias molestias iusto eos voluptatum.
        </p> */}
      </main>
    </>
  );
}

export default App;
